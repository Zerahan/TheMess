// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCameraPawn.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "Engine/CollisionProfile.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Game/WorldManager.h"
#include "PaperTileLayer.h"
#include "Buildings/BasicBuilding.h"
#include "UI/BasicUserHUDWidget.h"

// Sets default values
APlayerCameraPawn::APlayerCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CameraZoomBounds = FVector2D(512, 4096);

	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch	= false;
	bUseControllerRotationYaw	= false;
	bUseControllerRotationRoll	= false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->InitCapsuleSize(40.f, 40.f);
	CapsuleComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

	CapsuleComponent->CanCharacterStepUpOn = ECB_No;
	CapsuleComponent->SetShouldUpdatePhysicsVolume(true);
	CapsuleComponent->SetCanEverAffectNavigation(false);
	CapsuleComponent->bDynamicObstacle = true;
	RootComponent = CapsuleComponent;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 500.0f;
	//CameraBoom->SocketOffset = FVector(0.f, 0.f, 75.f);
	//CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));

	// Create an orthographic camera (no perspective) and attach it to the boom
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->ProjectionMode = ECameraProjectionMode::Orthographic;
	TopDownCamera->OrthoWidth = 2048.0f;
	TopDownCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	
	// Prevent all automatic rotation behavior on the camera, character, and camera component
	//CameraBoom->SetUsingAbsoluteRotation(true);
	TopDownCamera->bUsePawnControlRotation = false;
	TopDownCamera->bAutoActivate = true;

	FloatingPawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovementComponent"));

	ZoomStep = 10;

	CurrentClickCommand = EOnClickCommand::CMD_None;
	CommandCursors.AddDefaulted(3);
	CommandCursors[(uint8)EOnClickCommand::CMD_None]	= EMouseCursor::GrabHand;
	CommandCursors[(uint8)EOnClickCommand::CMD_Destroy]	= EMouseCursor::Crosshairs;
	CommandCursors[(uint8)EOnClickCommand::CMD_Place]	= EMouseCursor::EyeDropper;
}

// Called when the game starts or when spawned
void APlayerCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 0));
	if (MinSpeedDefault == 0) {
		MinSpeedDefault = FloatingPawnMovementComponent->MaxSpeed * 0.4f;
	}
	if (MaxSpeedDefault == 0) {
		MaxSpeedDefault = FloatingPawnMovementComponent->MaxSpeed;
	}

	WorldManagerRef = Cast<AWorldManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AWorldManager::StaticClass()));
	UpdateCameraZoom();
}

void APlayerCameraPawn::SetCursor(EMouseCursor::Type Cursor)
{
	if (!IsValid(PlayerControllerRef)) { return; }
	PlayerControllerRef->CurrentMouseCursor = Cursor;
}

// Called every frame
void APlayerCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsMouseDragging && IsLastMouseWorldLocationValid) {
		float Dx, Dy;
		PlayerControllerRef->GetInputMouseDelta(Dx, Dy);

		Dx *= DistanceRatio;
		Dy *= DistanceRatio;

		FVector WorldOffset = FVector(Dx, -Dy, 0);
		if (WorldOffset.Size() > 0.1f) {
			SetActorLocation(WorldManagerRef->ClampToBounds(GetActorLocation() - WorldOffset));
		}
	}
	IsLastMouseWorldLocationValid = GetMouseWorldPosition(LastMouseWorldLocation);
}


// Called to bind functionality to input
void APlayerCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCameraPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCameraPawn::MoveRight);
	PlayerInputComponent->BindAxis("CameraZoom", this, &APlayerCameraPawn::CameraZoom);

	PlayerInputComponent->BindAction("ShowGrid", IE_Pressed, this, &APlayerCameraPawn::ToggleGrid);
	
	PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &APlayerCameraPawn::PrimaryAction_Pressed);
	PlayerInputComponent->BindAction("PrimaryAction", IE_Released, this, &APlayerCameraPawn::PrimaryAction_Released);
	PlayerInputComponent->BindAction("SecondaryAction", IE_Pressed, this, &APlayerCameraPawn::SecondaryAction_Pressed);
	PlayerInputComponent->BindAction("SecondaryAction", IE_Released, this, &APlayerCameraPawn::SecondaryAction_Released);
}

UPawnMovementComponent* APlayerCameraPawn::GetMovementComponent() const
{
	return FloatingPawnMovementComponent;
}

void APlayerCameraPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	PlayerControllerRef = Cast<APlayerController>(NewController);
	if (IsValid(PlayerControllerRef)) {
		PlayerControllerRef->bShowMouseCursor = true;
		FInputModeGameAndUI InputMode = FInputModeGameAndUI();
		InputMode.SetHideCursorDuringCapture(false);
		PlayerControllerRef->SetInputMode(InputMode);
		SetPrimaryActionCommand(EOnClickCommand::CMD_None);

		if (HudWidgetClass) {
			HudWidgetRef = CreateWidget<UBasicUserHUDWidget>(PlayerControllerRef, HudWidgetClass, "HudWidget");
			HudWidgetRef->AddToViewport();
		}
	}
}

void APlayerCameraPawn::MoveForward(float AxisValue)
{
	if (AxisValue != 0.f) {
		if (WorldManagerRef) {
			switch (WorldManagerRef->IsInBoundsX(GetActorLocation())) {
			case -1:
				if (AxisValue > 0) { AddMovementInput(GetActorForwardVector(), AxisValue); }
				break;
			case 0:
				AddMovementInput(GetActorForwardVector(), AxisValue);
				break;
			case 1:
				if (AxisValue < 0) { AddMovementInput(GetActorForwardVector(), AxisValue); }
				break;
			}
		}
		//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, (AxisValue > 0 ? "MoveForward" : "MoveBackward"));
	}
}

void APlayerCameraPawn::MoveRight(float AxisValue)
{
	if (AxisValue != 0.f) {
		if (WorldManagerRef) {
			switch (WorldManagerRef->IsInBoundsY(GetActorLocation())) {
			case -1:
				if (AxisValue > 0) { AddMovementInput(GetActorRightVector(), AxisValue); }
				break;
			case 0:
				AddMovementInput(GetActorRightVector(), AxisValue);
				break;
			case 1:
				if (AxisValue < 0) { AddMovementInput(GetActorRightVector(), AxisValue); }
				break;
			}
		}
		//AddMovementInput(GetActorRightVector(), AxisValue);
		//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, (AxisValue > 0 ? "MoveRight" : "MoveLeft"));
	}
}

void APlayerCameraPawn::CameraZoom(float AxisValue)
{
	if (AxisValue != 0.f) {
		ZoomStep = FMath::Clamp(ZoomStep + FMath::RoundFromZero(AxisValue), 0.f, 20.f);
		UpdateCameraZoom();
	}
}

void APlayerCameraPawn::UpdateCameraZoom()
{
	float minZoom = FMath::Loge(CameraZoomBounds.X);
	TopDownCamera->OrthoWidth = FMath::Exp(minZoom + (FMath::Loge(CameraZoomBounds.Y) - minZoom) * ZoomStep / 19);
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Zoom Target: " + FString::SanitizeFloat(TopDownCamera->OrthoWidth));
	FloatingPawnMovementComponent->MaxSpeed = MinSpeedDefault + (MaxSpeedDefault - MinSpeedDefault) * (ZoomStep / 20.f);
}

void APlayerCameraPawn::ToggleGrid()
{
	if (IsValid(WorldManagerRef)) {
		WorldManagerRef->ToggleGrid();
	}
}

void APlayerCameraPawn::PrimaryAction_Pressed_Implementation()
{
	FVector TargetLocation;
	if (GetMouseWorldPosition(TargetLocation)) {
		ExecuteCurrentCommand(TargetLocation);
	}
}

void APlayerCameraPawn::PrimaryAction_Released_Implementation()
{
}

void APlayerCameraPawn::SecondaryAction_Pressed_Implementation()
{
	GetWorld()->GetTimerManager().SetTimer(MouseDragTimerHandle, this, &APlayerCameraPawn::DragTimerFinished, 0.1f, false);
}

void APlayerCameraPawn::SecondaryAction_Released_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(MouseDragTimerHandle);
	if (!IsMouseDragging) {
		SetPrimaryActionCommand(EOnClickCommand::CMD_None);
	}
	IsMouseDragging = false;
}

void APlayerCameraPawn::DragTimerFinished()
{
	ActorDrag_StartLocation = GetActorLocation();
	MouseDrag_StartLocation = GetMousePosition();

	FVector StartLocation;
	FVector Direction;
	if (!PlayerControllerRef->DeprojectScreenPositionToWorld(MouseDrag_StartLocation.X+10, MouseDrag_StartLocation.Y, StartLocation, Direction)) { return; }
	FVector OldMouseWorldLocation = FMath::LinePlaneIntersection(StartLocation, StartLocation + Direction, FVector(0, 0, 0), FVector::UpVector);

	FVector MouseWorldLocation;
	GetMouseWorldPosition(MouseWorldLocation);

	DistanceRatio = FVector::Distance(OldMouseWorldLocation, MouseWorldLocation) / FVector2D::Distance(FVector2D(MouseDrag_StartLocation.X + 10, MouseDrag_StartLocation.Y), MouseDrag_StartLocation);
	DistanceRatio *= 16;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "MousePos: " + FString::SanitizeFloat(MouseDrag_StartLocation.X,1) + ", " + FString::SanitizeFloat(MouseDrag_StartLocation.Y, 1));
	IsMouseDragging = true;
}

void APlayerCameraPawn::ExecuteCurrentCommand_Implementation(const FVector HitLocation)
{
	if (!IsValid(WorldManagerRef)) { return; }
	switch (CurrentClickCommand)
	{
	case EOnClickCommand::CMD_Place:
		if (SelectedBuildingClass) {
			FVector SnappedLocation = WorldManagerRef->SnapLocationToGrid(HitLocation);
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
			ABasicBuilding* SpawnedActor = GetWorld()->SpawnActor<ABasicBuilding>(SelectedBuildingClass, SnappedLocation, FRotator(0,0,0), SpawnInfo);
		}
		//WorldManagerRef->SetTileFromWorld(HitLocation, FPaperTileInfo());
		break;
	case EOnClickCommand::CMD_Destroy:
		break;
	case EOnClickCommand::CMD_None:
		break;
	default:
		break;
	}
}

void APlayerCameraPawn::SetPrimaryActionCommand_Implementation(const EOnClickCommand Command)
{
	CurrentClickCommand = Command;
	if (CommandCursors.IsValidIndex((uint8)Command)) {
		SetCursor(CommandCursors[(uint8)Command]);
	}
	else {
		SetCursor(EMouseCursor::Default);
	}
}

FVector2D APlayerCameraPawn::GetMousePosition() const
{
	float X, Y;
	PlayerControllerRef->GetMousePosition(X, Y);
	return FVector2D(X, Y);
}

bool APlayerCameraPawn::GetMouseWorldPosition(FVector& WorldLocation) const
{
	if (!IsValid(PlayerControllerRef)) { return false; }
	FVector StartLocation;
	FVector Direction;
	if (!PlayerControllerRef->DeprojectMousePositionToWorld(StartLocation, Direction)) { return false; }
	WorldLocation = FMath::LinePlaneIntersection(StartLocation, StartLocation + Direction, FVector(0, 0, 0), FVector::UpVector);
	return true;
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCameraPawn.generated.h"

UENUM(BlueprintType, Category = "Player|Command")
enum class EOnClickCommand : uint8 {
	CMD_None	UMETA(DisplayName = "None"),
	CMD_Place	UMETA(DisplayName = "Place"),
	CMD_Destroy	UMETA(DisplayName = "Destroy"),
};

UCLASS(Blueprintable, Abstract, config = Game)
class AGORA_API APlayerCameraPawn : public APawn
{
	GENERATED_BODY()

	/** The CapsuleComponent being used for movement collision (by CharacterMovement). Always treated as being vertically aligned in simple collision check functions. */
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCamera;

	/** Camera boom positioning the camera over the pawn */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Camera boom positioning the camera over the pawn */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UFloatingPawnMovement* FloatingPawnMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class AWorldManager* WorldManagerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class APlayerController* PlayerControllerRef;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float MinSpeedDefault;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float MaxSpeedDefault;

	UPROPERTY(BlueprintReadOnly, Category = "Player|Command", meta = (AllowPrivateAccess = "true"))
	EOnClickCommand CurrentClickCommand;

	UPROPERTY(BlueprintReadOnly, Category = "Player|Control", meta = (AllowPrivateAccess = "true"))
	bool IsLastMouseWorldLocationValid;

	UPROPERTY(BlueprintReadOnly, Category = "Player|Control", meta = (AllowPrivateAccess = "true"))
	FVector LastMouseWorldLocation;

	UPROPERTY(BlueprintReadOnly, Category = "Player|Control", meta = (AllowPrivateAccess = "true"))
	FVector ActorDrag_StartLocation;

	UPROPERTY(BlueprintReadOnly, Category = "Player|Control", meta = (AllowPrivateAccess = "true"))
	FVector2D MouseDrag_StartLocation;

	UPROPERTY()
	float DistanceRatio;

	UPROPERTY(BlueprintReadOnly, Category = "Player|Control", meta = (AllowPrivateAccess = "true"))
	bool IsMouseDragging;

	UPROPERTY(BlueprintReadOnly, Category = "Player|Control", meta = (AllowPrivateAccess = "true"))
	FTimerHandle MouseDragTimerHandle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player|Control", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABasicBuilding> SelectedBuildingClass;

	UFUNCTION()
	void DragTimerFinished();

public:
	// Sets default values for this pawn's properties
	APlayerCameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player|Control")
	FVector2D CameraZoomBounds;

	UPROPERTY()
	int32 ZoomStep;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player|Command")
	TArray<TEnumAsByte<EMouseCursor::Type>> CommandCursors;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player|UI")
	TSubclassOf<class UBasicUserHUDWidget> HudWidgetClass;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Player|UI")
	class UBasicUserHUDWidget* HudWidgetRef;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetCursor(EMouseCursor::Type Cursor);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION()
	void MoveForward(float AxisValue);

	UFUNCTION()
	void MoveRight(float AxisValue);

	UFUNCTION()
	void CameraZoom(float AxisValue);

	UFUNCTION()
	void UpdateCameraZoom();

	UFUNCTION()
	void ToggleGrid();

	UFUNCTION(BlueprintNativeEvent, Category = "Player|Command")
	void PrimaryAction_Pressed(); // For BlueprintNativeEvent, an automatically-generated function that allows blueprints to override the default c++ behavior defined in [FunctionName]_Implementation()
	virtual void PrimaryAction_Pressed_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Player|Command")
	void PrimaryAction_Released();
	virtual void PrimaryAction_Released_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Player|Command")
	void SecondaryAction_Pressed();
	virtual void SecondaryAction_Pressed_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Player|Command")
	void SecondaryAction_Released();
	virtual void SecondaryAction_Released_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Player|Command")
	void ExecuteCurrentCommand(const FVector HitLocation);
	virtual void ExecuteCurrentCommand_Implementation(const FVector HitLocation);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Player|Command")
	void SetPrimaryActionCommand(const EOnClickCommand Command);
	virtual void SetPrimaryActionCommand_Implementation(const EOnClickCommand Command);

	UFUNCTION(BlueprintCallable, Category = "Player|Control")
	FVector2D GetMousePosition() const;

	UFUNCTION(BlueprintCallable, Category = "Player|Control")
	bool GetMouseWorldPosition(FVector& WorldLocation) const;

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCamera; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

};

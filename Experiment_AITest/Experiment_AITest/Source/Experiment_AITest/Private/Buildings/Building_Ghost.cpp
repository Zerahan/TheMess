// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/Building_Ghost.h"
#include "Buildings/Building_Basic.h"

// Sets default values
ABuilding_Ghost::ABuilding_Ghost()
	:Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default Root Object"));
	
	if (BuildingClassRef) {
		ABuilding_Basic* Building = BuildingClassRef->GetDefaultObject<ABuilding_Basic>();
		TArray<UStaticMesh*> Meshes;
		TArray<FTransform> Transforms;
		Building->BuildGhost(Meshes, Transforms);
		for (int32 i = 0; i < Meshes.Num(); i++) {
			if (Transforms.IsValidIndex(i)) {
				UStaticMeshComponent* NewMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh" + i));
				if (NewMesh) {
					NewMesh->SetRelativeTransform(Transforms[i]);
					NewMesh->SetStaticMesh(Meshes[i]);
					if (GhostMaterial) {
						NewMesh->SetMaterial(0, GhostMaterial->GetDefaultMaterial(EMaterialDomain::MD_Surface));
					}
					NewMesh->SetupAttachment(RootComponent);
				}
			}
		}
	}
}

ABuilding_Ghost::ABuilding_Ghost(TSubclassOf<ABuilding_Basic> BuildingClass)
{
	Super();
	if (BuildingClass) {
		BuildingClassRef = BuildingClass;
		ABuilding_Basic* Building = BuildingClass->GetDefaultObject<ABuilding_Basic>();
		TArray<UStaticMesh*> Meshes;
		TArray<FTransform> Transforms;
		Building->BuildGhost(Meshes, Transforms);
		for (int32 i = 0; i < Meshes.Num(); i++) {
			if (Transforms.IsValidIndex(i)) {
				UStaticMeshComponent* NewMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh" + i));
				if (NewMesh) {
					NewMesh->SetRelativeTransform(Transforms[i]);
					NewMesh->SetStaticMesh(Meshes[i]);
					if (GhostMaterial) {
						NewMesh->SetMaterial(0, GhostMaterial->GetDefaultMaterial(EMaterialDomain::MD_Surface));
					}
				}
			}
		}
	}
}

// Called when the game starts or when spawned
void ABuilding_Ghost::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuilding_Ghost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABuilding_Ghost::CanPlaceGhost_Implementation() const { return true; }

void ABuilding_Ghost::OnPlaceGhost_Implementation()
{
	if (BuildingClassRef) {
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ABuilding_Basic* BuildingRef = GetWorld()->SpawnActor<ABuilding_Basic>(BuildingClassRef, GetActorTransform(), SpawnParameters);
		if (BuildingRef) {
			Destroy();
		}
	}
}


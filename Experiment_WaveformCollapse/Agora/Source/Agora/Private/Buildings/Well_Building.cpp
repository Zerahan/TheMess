// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/Well_Building.h"
#include "Buildings/BasicBuilding.h"
#include "Game/WorldManager.h"

AWell_Building::AWell_Building()
	:Super()
{
	MaxNumberOfBuildingsToAttract = 5;
	EffectiveRadius = 128;
}

void AWell_Building::BeginPlay()
{
	Super::BeginPlay();
	/*
	* This should be moved to the WorldManager.
	* Aka, the WorldManager checks to see if it can spawn more houses
	* If it can spawn more, it finds wells that have available capacity and spawns a house near the well.
	*/

	if (BuildingClassToAttract) {
		FVector SnappedLocation;
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
		for (int i = 0; i < MaxNumberOfBuildingsToAttract; i++) {
			SnappedLocation = WorldManagerRef->SnapLocationToGrid(GetActorLocation() + FMath::VRand() * EffectiveRadius);
			ABasicBuilding* SpawnedActor = GetWorld()->SpawnActor<ABasicBuilding>(BuildingClassToAttract, SnappedLocation, FRotator(0, 0, 0), SpawnInfo);
		}
	}
}

// Called every frame
void AWell_Building::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
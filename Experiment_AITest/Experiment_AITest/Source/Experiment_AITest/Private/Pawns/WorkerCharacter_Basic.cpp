// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/WorkerCharacter_Basic.h"
#include "Kismet/GameplayStatics.h"
#include "Buildings/WorkableBuilding_Basic.h"
#include "Inventory/StorageComponent.h"

AWorkerCharacter_Basic::AWorkerCharacter_Basic()
	: Super()
{
	StorageComponent = CreateDefaultSubobject<UStorageComponent>(TEXT("StorageComponent"));
}

bool AWorkerCharacter_Basic::SetupAssignments()
{
	if (IsValid(AssignedWorksite)) {
		AssignedWorksite->UnassignWorker(this);
		AssignedWorksite = nullptr;
	}
	if (IsValid(AssignedHouse)) {
		AssignedHouse->UnassignWorker(this);
		AssignedHouse = nullptr;
	}
	for ( TSubclassOf<AWorkableBuilding_Basic> WorksiteClass : ValidWorksiteClasses) {
		if (IsValid(AssignedWorksite)) break;
		TArray<AActor*> Worksites;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), WorksiteClass, Worksites);
		for (AActor* ActorSite : Worksites) {
			AWorkableBuilding_Basic* Worksite = Cast<AWorkableBuilding_Basic>(ActorSite);
			if (IsValid(Worksite)) {
				if (Worksite->AssignNewWorker(this)) {
					AssignedWorksite = Worksite;
					break;
				}
			}
		}
	}
	for (TSubclassOf<AWorkableBuilding_Basic> HouseClass : ValidHouseClasses) {
		if (IsValid(AssignedHouse)) break;
		TArray<AActor*> Houses;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), HouseClass, Houses);
		for (AActor* ActorSite : Houses) {
			AWorkableBuilding_Basic* House = Cast<AWorkableBuilding_Basic>(ActorSite);
			if (IsValid(House)) {
				if (House->AssignNewWorker(this)) {
					AssignedHouse = House;
					break;
				}
			}
		}
	}
	return IsValid(AssignedWorksite) && IsValid(AssignedHouse);
}

AWorkableBuilding_Basic* AWorkerCharacter_Basic::GetAssignedWorksite() const {
	return AssignedWorksite;
}

AWorkableBuilding_Basic* AWorkerCharacter_Basic::GetAssignedHouse() const {
	return AssignedHouse;
}

UStorageComponent* AWorkerCharacter_Basic::GetStorageComponent_Implementation() const {
	return StorageComponent;
}

uint8 AWorkerCharacter_Basic::TransferItemToStorage_Implementation(UItemData* ItemDataToAdd, int32& Remaining)
{
	if (!IsValid(Execute_GetStorageComponent(this))) return (uint8)EError::INVALID;
	return Execute_GetStorageComponent(this)->TransferItemToStorage(ItemDataToAdd, Remaining);
}

uint8 AWorkerCharacter_Basic::AddItemToStorage_Implementation(int32 Amount, TSubclassOf<UDataAsset> StaticData, int32& Remaining)
{
	if (!IsValid(Execute_GetStorageComponent(this))) return (uint8)EError::INVALID;
	return Execute_GetStorageComponent(this)->AddItemToStorage(Amount, StaticData, Remaining);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/WorkerCharacter_Basic.h"
#include "Kismet/GameplayStatics.h"
#include "Buildings/WorkableBuilding_Basic.h"

AWorkerCharacter_Basic::AWorkerCharacter_Basic()
	: Super()
{
	//StorageComponent = CreateDefaultSubobject<UStorageComponent>(TEXT("StorageComponent"));
}

bool AWorkerCharacter_Basic::SetupAssignments()
{
	return AssignWorksite() && AssignHouse();
}

bool AWorkerCharacter_Basic::AssignWorksite(bool ForceNew)
{
	if (IsValid(AssignedWorksite)) {
		if (!ForceNew) return true;
		AssignedWorksite->UnassignWorker(this);
		AssignedWorksite = nullptr;
	}

	TArray<AActor*> Worksites;
	for (TSubclassOf<AWorkableBuilding_Basic> WorksiteClass : ValidWorksiteClasses) {
		if (IsValid(AssignedWorksite)) break;
		TArray<AActor*> NewWorksites;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), WorksiteClass, NewWorksites);
		Worksites.Append(NewWorksites);
	}

	// Attempt to assign the worker while obaying the one-unit limit.
	for (AActor* ActorSite : Worksites) {
		AWorkableBuilding_Basic* Worksite = Cast<AWorkableBuilding_Basic>(ActorSite);
		if (IsValid(Worksite)) {
			if (Worksite->AssignNewWorker(this)) {
				AssignedWorksite = Worksite;
				break;
			}
		}
	}

	// Attempt again but ignore the one-unit limit this time.
	if (!IsValid(AssignedWorksite)) {
		for (AActor* ActorSite : Worksites) {
			AWorkableBuilding_Basic* Worksite = Cast<AWorkableBuilding_Basic>(ActorSite);
			if (IsValid(Worksite)) {
				if (Worksite->AssignNewWorker(this, true)) {
					AssignedWorksite = Worksite;
					break;
				}
			}
		}
	}
	return IsValid(AssignedWorksite);
}

bool AWorkerCharacter_Basic::AssignHouse(bool ForceNew)
{
	if (IsValid(AssignedHouse)) {
		if (!ForceNew) return true;
		AssignedHouse->UnassignWorker(this);
		AssignedHouse = nullptr;
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
	return IsValid(AssignedHouse);
}

bool AWorkerCharacter_Basic::GetIsIdle() const { return !IsValid(AssignedHouse) || !IsValid(AssignedWorksite); }

AWorkableBuilding_Basic* AWorkerCharacter_Basic::GetAssignedWorksite() const {
	return AssignedWorksite;
}

AWorkableBuilding_Basic* AWorkerCharacter_Basic::GetAssignedHouse() const {
	return AssignedHouse;
}

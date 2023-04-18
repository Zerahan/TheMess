// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/FactionHandlerComponent.h"
#include "Buildings/WorkableBuilding_Basic.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/WorkerCharacter_Basic.h"

// Sets default values for this component's properties
UFactionHandlerComponent::UFactionHandlerComponent()
	: Super()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFactionHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UFactionHandlerComponent::SetupFaction_Implementation()
{
	FactionData = NewObject<UFactionData>(this);
}

// Called every frame
void UFactionHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int32 UFactionHandlerComponent::GetFoodCount() const { return IsValid(FactionData) ? FactionData->FoodCount : -1; }

int32 UFactionHandlerComponent::GetPopulationCount() const { return IsValid(FactionData) ? FactionData->PopulationCount : -1; }

int32 UFactionHandlerComponent::SetFoodCount(int32 NewValue, bool ModifyValue) {
	if (!IsValid(FactionData)) return -1;
	if (ModifyValue && NewValue == 0) return FactionData->FoodCount;
	if (!ModifyValue && NewValue == FactionData->FoodCount) return FactionData->FoodCount;
	FactionData->FoodCount = (ModifyValue ? NewValue + FactionData->FoodCount : NewValue);
	UpdateFoodCount.Broadcast(FactionData->FoodCount);
	return FactionData->FoodCount;
}

int32 UFactionHandlerComponent::SetPopulationCount(int32 NewValue, bool ModifyValue) {
	if (!IsValid(FactionData)) return -1;
	if (ModifyValue && NewValue == 0) return FactionData->PopulationCount;
	if (!ModifyValue && NewValue == FactionData->PopulationCount) return FactionData->PopulationCount;
	FactionData->PopulationCount = (ModifyValue ? NewValue + FactionData->PopulationCount : NewValue);
	UpdatePopulationCount.Broadcast(FactionData->PopulationCount);
	return FactionData->PopulationCount;
}

UFactionData* UFactionHandlerComponent::GetFactionData() const { return (IsValid(FactionData) ? FactionData : nullptr); }

void UFactionHandlerComponent::OnConstructedBuilding_Implementation(AActor* BuildingRef) const
{
	AWorkableBuilding_Basic* WorkableBuilding = Cast<AWorkableBuilding_Basic>(BuildingRef);
	if (IsValid(WorkableBuilding)) {
		TArray<AActor*> Workers;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWorkerCharacter_Basic::StaticClass(), Workers);
		bool FoundIdleWorkers = false;
		for (int32 i = 0; i < Workers.Num(); i++) {
			AWorkerCharacter_Basic* Worker = Cast<AWorkerCharacter_Basic>(Workers[i]);
			if (Worker) {
				if (Worker->GetIsIdle()) {
					Worker->SetupAssignments();
					FoundIdleWorkers = true;
				}
			}
		}
		if (!FoundIdleWorkers) {
			for (int32 i = 0; i < Workers.Num(); i++) {
				AWorkerCharacter_Basic* Worker = Cast<AWorkerCharacter_Basic>(Workers[i]);
				if (Worker) {
					if (Worker->GetAssignedWorksite()->GetAssignedWorkerCount() > 1) {
						Worker->AssignWorksite(true);
					}
				}
			}
		}
	}
}

void UFactionHandlerComponent::OnDestroyedBuilding_Implementation(AActor* BuildingRef) const
{
}

void UFactionHandlerComponent::OnAddedUnit_Implementation(AActor* UnitRef) const
{
}

void UFactionHandlerComponent::OnRemovedUnit_Implementation(AActor* UnitRef) const
{
}

UFactionData::UFactionData()
	: Super()
{
	FoodCount = 0;
	PopulationCount = 0;
}

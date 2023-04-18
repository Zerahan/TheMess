// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AITest_GameState.h"
#include "Game/FactionHandlerComponent.h"

void AAITest_GameState::BeginPlay()
{
	for (int32 i = 0; i < FactionCount; i++) {
		FactionHandlers[i]->SetupFaction();
	}
}

AAITest_GameState::AAITest_GameState()
	: Super()
{
	FactionCount = 1;
	
	for (EFaction Faction : TEnumRange<EFaction>()) {
		UFactionHandlerComponent* Handler = CreateDefaultSubobject<UFactionHandlerComponent>(FName(UEnum::GetValueAsName(Faction).ToString() + " Handler"));
		Handler->Faction = Faction;
		FactionHandlers.Add(Handler);
	}
}

void AAITest_GameState::OnConstructedBuilding_Implementation(EFaction Faction, AActor* BuildingRef) const
{
	if(!IsValid(Execute_GetFactionHandler(this, Faction))) return;
	Execute_GetFactionHandler(this, Faction)->OnConstructedBuilding(BuildingRef);
}

void AAITest_GameState::OnDestroyedBuilding_Implementation(EFaction Faction, AActor* BuildingRef) const
{
	if (!IsValid(Execute_GetFactionHandler(this, Faction))) return;
	Execute_GetFactionHandler(this, Faction)->OnDestroyedBuilding(BuildingRef);
}

void AAITest_GameState::OnAddedUnit_Implementation(EFaction Faction, AActor* UnitRef) const
{
	if (!IsValid(Execute_GetFactionHandler(this, Faction))) return;
	Execute_GetFactionHandler(this, Faction)->OnAddedUnit(UnitRef);
}

void AAITest_GameState::OnRemovedUnit_Implementation(EFaction Faction, AActor* UnitRef) const
{
	if (!IsValid(Execute_GetFactionHandler(this, Faction))) return;
	Execute_GetFactionHandler(this, Faction)->OnRemovedUnit(UnitRef);
}

void AAITest_GameState::AssignControllerToFaction_Implementation(AController* Controller, EFaction Faction)
{
	ControllerFactionAssignments.Add(Controller, Faction);
	GEngine->AddOnScreenDebugMessage(-1,10,FColor::Cyan,FString::Printf(TEXT("Assigning (%s) to %s"), *Controller->GetName(), *UEnum::GetValueAsName(Faction).ToString()));
}

void AAITest_GameState::UnassignController_Implementation(AController* Controller)
{
	if (ControllerFactionAssignments.Find(Controller)) {
		ControllerFactionAssignments.Remove(Controller);
	}
}

UFactionHandlerComponent* AAITest_GameState::GetFactionHandler_Implementation(EFaction Faction) const
{
	if (FactionHandlers.IsValidIndex((uint8)Faction)) {
		return FactionHandlers[(uint8)Faction];
	}
	return nullptr;
}

UFactionHandlerComponent* AAITest_GameState::GetFactionHandlerFromController_Implementation(AController* Controller) const
{
	if (ControllerFactionAssignments.Contains(Controller)) {
		return Execute_GetFactionHandler(this, *ControllerFactionAssignments.Find(Controller));
	}
	return nullptr;
}

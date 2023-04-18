// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Interfaces/FactionInterface.h"
#include "AITest_GameState.generated.h"

class UFactionHandlerComponent;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class EXPERIMENT_AITEST_API AAITest_GameState : public AGameState , public IFactionInterface
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	uint8 FactionCount;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<UFactionHandlerComponent*> FactionHandlers;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TMap<AController*, EFaction> ControllerFactionAssignments;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	AAITest_GameState();
	
	//IFactionInterface
	virtual void OnConstructedBuilding_Implementation(EFaction Faction, AActor* BuildingRef) const;
	virtual void OnDestroyedBuilding_Implementation(EFaction Faction, AActor* BuildingRef) const;
	virtual void OnAddedUnit_Implementation(EFaction Faction, AActor* UnitRef) const;
	virtual void OnRemovedUnit_Implementation(EFaction Faction, AActor* UnitRef) const;
	
	virtual void AssignControllerToFaction_Implementation(AController* Controller, EFaction Faction);
	virtual void UnassignController_Implementation(AController* Controller);
	virtual UFactionHandlerComponent* GetFactionHandler_Implementation(EFaction Faction) const;
	virtual UFactionHandlerComponent* GetFactionHandlerFromController_Implementation(AController* Controller) const;
};

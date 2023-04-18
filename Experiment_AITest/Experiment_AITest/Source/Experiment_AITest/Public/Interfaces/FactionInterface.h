// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/FactionTypes.h"
#include "FactionInterface.generated.h"

class UFactionHandlerComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFactionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class EXPERIMENT_AITEST_API IFactionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnConstructedBuilding(EFaction Faction, AActor* BuildingRef) const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnDestroyedBuilding(EFaction Faction, AActor* BuildingRef) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnAddedUnit(EFaction Faction, AActor* UnitRef) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnRemovedUnit(EFaction Faction, AActor* UnitRef) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AssignControllerToFaction(AController* Controller, EFaction Faction);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UnassignController(AController* Controller);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UFactionHandlerComponent* GetFactionHandler(EFaction Faction) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UFactionHandlerComponent* GetFactionHandlerFromController(AController* Controller) const;
};

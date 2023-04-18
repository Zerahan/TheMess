// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/FactionTypes.h"
#include "FactionHandlerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateFoodCount, int32, Count);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdatePopulationCount, int32, Count);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXPERIMENT_AITEST_API UFactionHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	UFactionData* FactionData;

public:	
	// Sets default values for this component's properties
	UFactionHandlerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	EFaction Faction;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetupFaction();
	virtual void SetupFaction_Implementation();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	int32 GetFoodCount() const;

	UFUNCTION(BlueprintCallable)
	int32 GetPopulationCount() const;

	UFUNCTION(BlueprintCallable)
	int32 SetFoodCount(int32 NewValue, bool ModifyValue = true);

	UFUNCTION(BlueprintCallable)
	int32 SetPopulationCount(int32 NewValue, bool ModifyValue = true);

	UPROPERTY(BlueprintAssignable)
	FUpdateFoodCount UpdateFoodCount;

	UPROPERTY(BlueprintAssignable)
	FUpdatePopulationCount UpdatePopulationCount;

	UFUNCTION(BlueprintCallable)
	UFactionData* GetFactionData() const;


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnConstructedBuilding(AActor* BuildingRef) const;
	virtual void OnConstructedBuilding_Implementation(AActor* BuildingRef) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnDestroyedBuilding(AActor* BuildingRef) const;
	virtual void OnDestroyedBuilding_Implementation(AActor* BuildingRef) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnAddedUnit(AActor* UnitRef) const;
	virtual void OnAddedUnit_Implementation(AActor* UnitRef) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnRemovedUnit(AActor* UnitRef) const;
	virtual void OnRemovedUnit_Implementation(AActor* UnitRef) const;
};

UCLASS(BlueprintType)
class EXPERIMENT_AITEST_API UFactionData : public UObject
{
	GENERATED_BODY()

public:
	UFactionData();

	UPROPERTY()
	int32 FoodCount;

	UPROPERTY()
	int32 PopulationCount;
};

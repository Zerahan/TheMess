// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "AITest_GameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateFoodCount, int32, Count);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdatePopulationCount, int32, Count);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class EXPERIMENT_AITEST_API AAITest_GameState : public AGameState
{
	GENERATED_BODY()

	UPROPERTY()
	int32 FoodCount;

	UPROPERTY()
	int32 PopulationCount;
	
public:
	AAITest_GameState();

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
};

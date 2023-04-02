// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AITest_GameState.h"

AAITest_GameState::AAITest_GameState()
	: Super()
{
	FoodCount = 0;
	PopulationCount = 0;
}

int32 AAITest_GameState::GetFoodCount() const { return FoodCount; }

int32 AAITest_GameState::GetPopulationCount() const { return PopulationCount; }

int32 AAITest_GameState::SetFoodCount(int32 NewValue, bool ModifyValue) {
	if(ModifyValue && NewValue == 0) return FoodCount;
	if(!ModifyValue && NewValue == FoodCount) return FoodCount;
	FoodCount = (ModifyValue ? NewValue + FoodCount : NewValue);
	UpdateFoodCount.Broadcast(FoodCount);
	return FoodCount;
}

int32 AAITest_GameState::SetPopulationCount(int32 NewValue, bool ModifyValue) {
	if (ModifyValue && NewValue == 0) return PopulationCount;
	if (!ModifyValue && NewValue == PopulationCount) return PopulationCount;
	PopulationCount = (ModifyValue ? NewValue + PopulationCount : NewValue);
	UpdatePopulationCount.Broadcast(PopulationCount);
	return PopulationCount;
}

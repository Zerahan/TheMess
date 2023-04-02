// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BuildingFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class EXPERIMENT_AITEST_API UBuildingFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	static int32 FindClosestActorInArray(TArray<AActor*> Actors, AActor* OriginActor);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AITestAssetManager.generated.h"

class UBuildingDataAsset;

/**
 * 
 */
UCLASS()
class EXPERIMENT_AITEST_API UAITestAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	UAITestAssetManager(){}

	virtual void StartInitialLoading() override;

	static const FPrimaryAssetType	BuildingType;

	static UAITestAssetManager& Get();

	UFUNCTION(BlueprintCallable)
	static UAITestAssetManager* GetManager();
	
	UFUNCTION(BlueprintCallable)
	UBuildingDataAsset* ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning = true);
};

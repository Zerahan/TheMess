// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AITestAssetManager.h"
#include "Data/BuildingDataAsset.h"
#include "AbilitySystemGlobals.h"

const FPrimaryAssetType UAITestAssetManager::BuildingType = TEXT("Building");

void UAITestAssetManager::StartInitialLoading()
{
    Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
}

UAITestAssetManager& UAITestAssetManager::Get()
{
    UAITestAssetManager* This = Cast<UAITestAssetManager>(GEngine->AssetManager);

    if (This)
    {
        return *This;
    }
    else {
        UE_LOG(LogTemp, Fatal, TEXT("Invalid AssetManager in DefaultEngine.ini"));
        return *NewObject<UAITestAssetManager>();
    }
}

UAITestAssetManager* UAITestAssetManager::GetManager() { return &Get(); }

UBuildingDataAsset* UAITestAssetManager::ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning)
{
    FSoftObjectPath ObjPath = GetPrimaryAssetPath(PrimaryAssetId);

    UBuildingDataAsset* LoadedObj = Cast<UBuildingDataAsset>(ObjPath.TryLoad());
    return LoadedObj;
}

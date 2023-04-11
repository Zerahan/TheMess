// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/BuildingDataAsset.h"

FString UBuildingDataAsset::GetIdentifierString() const
{
	return GetPrimaryAssetId().ToString();
}

FPrimaryAssetId UBuildingDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(ItemType, GetFName());
}

UTexture2D* UBuildingDataAsset::GetIcon() const { return Icon.Get(); }

bool UBuildingDataAsset::IsValidWorkType(EWorkType WorkType) const {
	return WorkInfo.Contains(WorkType);
}

void UBuildingDataAsset::DoProduction(AActor* ParentActor, EWorkType WorkType) const
{
	/*
	TArray<UItemData*> Produce;
	TArray<FItemData_Struct> ProduceData = WorkInfo.Find(WorkType)->Production;
	if (ProduceData.Num() > 0) {
		for (auto ItemData : ProduceData) {
			UItemData* Item = NewObject<UItemData>(ParentActor);
			Item->SetupFromRaw(ItemData.Amount, ItemData.StaticData);
			Produce.Add(Item);
		}
	}
	//*/
	return;
}

TArray<TSubclassOf<UDataAsset>> UBuildingDataAsset::GetProduction(EWorkType WorkType) const
{
	return TArray<TSubclassOf<UDataAsset>>();
}

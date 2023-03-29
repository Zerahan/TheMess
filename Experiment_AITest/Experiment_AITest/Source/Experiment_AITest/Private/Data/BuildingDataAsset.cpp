// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/BuildingDataAsset.h"
#include "Inventory/ItemData.h"

UBuildingDataAsset::UBuildingDataAsset()
{
	DisplayName = FText::FromString("Undefined");
}

bool UBuildingDataAsset::IsValidWorkType(EWorkType WorkType) const {
	return WorkInfo.Contains(WorkType);
}

TArray<UItemData*> UBuildingDataAsset::DoProduction(AActor* ParentActor, EWorkType WorkType) const
{
	TArray<UItemData*> Produce;
	TArray<FItemData_Struct> ProduceData = WorkInfo.Find(WorkType)->Production;
	if (ProduceData.Num() > 0) {
		for (auto ItemData : ProduceData) {
			UItemData* Item = NewObject<UItemData>(ParentActor);
			Produce.Add(Item);
		}
	}
	return Produce;
}

TMap<EWorkType, FWorkData> UBuildingDataAsset::GetWorkInfo() const { return WorkInfo; }

// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/WorkableBuilding_Basic.h"
#include "Data/BuildingDataAsset.h"
#include "Inventory/ItemData.h"

void AWorkableBuilding_Basic::BeginPlay()
{
    if (IsValid(GetStaticData())) {
        TMap<EWorkType, FWorkData> Info = GetStaticData()->GetWorkInfo();
        TArray<EWorkType> Keys;
        Info.GetKeys(Keys);
        for (auto K : Keys) {
            IsWorkTypeAvailable.Add(K, false);
        }
    }
}

bool AWorkableBuilding_Basic::CanDoWork_Implementation(const AActor* Worker, const EWorkType WorkType, const UItemData* AvailableItem) const
{
    return false;
}

bool AWorkableBuilding_Basic::DoWork_Implementation(const AActor* Worker, const EWorkType WorkType, const UItemData* AvailableItem)
{
    return false;
}

int32 AWorkableBuilding_Basic::GetRequiredItem_Implementation(const EWorkType WorkType, TSubclassOf<UItemData>& ItemType) const
{
    return 0;
}

UBuildingDataAsset* AWorkableBuilding_Basic::GetStaticData() const { return StaticData; }

bool AWorkableBuilding_Basic::CanWorkBuilding(EWorkType WorkType) const {
    if (!IsValid(GetStaticData())) return false;
    if (!GetStaticData()->IsValidWorkType(WorkType)) return false;
    return *IsWorkTypeAvailable.Find(WorkType);
}

bool AWorkableBuilding_Basic::WorkBuilding_Implementation(AActor* WorkingActor, EWorkType WorkType, TArray<UItemData*>& ReturnedProduction)
{
    if(CanWorkBuilding(WorkType)) return false;
    ReturnedProduction = GetStaticData()->DoProduction(WorkingActor, WorkType);
    return true;
}

void AWorkableBuilding_Basic::UpdateWorkTypeAvailability(EWorkType WorkType, bool NewAvailability) {
    if(!IsWorkTypeAvailable.Contains(WorkType)) return;
    IsWorkTypeAvailable.Add(WorkType, NewAvailability);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/WorkableBuilding_Basic.h"
#include "Inventory/ItemData.h"

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

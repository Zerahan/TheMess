// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/StorageInterface.h"
#include "Inventory/StorageComponent.h"


// Add default functionality here for any IStorageInterface functions that are not pure virtual.

uint8 IStorageInterface::TransferItemToStorage_Implementation(UItemData* ItemDataToAdd, int32& Remaining)
{
    if (!IsValid(GetStorageComponent())) return (uint8)EError::INVALID;
    return GetStorageComponent()->TransferItemToStorage(ItemDataToAdd, Remaining);
}

uint8 IStorageInterface::AddItemToStorage_Implementation(int32 Amount, TSubclassOf<UDataAsset> StaticData, int32& Remaining)
{
    if (!IsValid(GetStorageComponent())) return (uint8)EError::INVALID;
    return GetStorageComponent()->AddItemToStorage(Amount, StaticData, Remaining);
}

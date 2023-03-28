// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/StorageComponent.h"
#include "Inventory/ItemData.h"

// Sets default values for this component's properties
UStorageComponent::UStorageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	MaxSlotCount = 8;
	WhitelistAllowedTypes = true;
	// ...
}


// Called when the game starts
void UStorageComponent::BeginPlay()
{
	Super::BeginPlay();
	ItemSlotList.SetNumUninitialized(MaxSlotCount);
	
	// ...
	
}


// Called every frame
void UStorageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<int32> UStorageComponent::FindMatchingSlots(const UItemData* ItemData, const bool IncludeEmpty) const
{
	TArray<int32> FoundSlotIndices;
	if (!IsValid(ItemData)) return FoundSlotIndices;
	if (!ItemData->IsValidData()) return FoundSlotIndices;
	TArray<int32> FoundEmptySlotIndices;
	for (int32 i = 0; i < ItemSlotList.Num(); i++) {
		if (!IsValid(ItemSlotList[i])) {
			if(IncludeEmpty) FoundEmptySlotIndices.Add(i);
		}else if (ItemSlotList[i]->GetStaticData() == ItemData->GetStaticData()) {
			FoundSlotIndices.Add(i);
		}
	}
	if (IncludeEmpty) FoundSlotIndices.Append(FoundEmptySlotIndices);
	return FoundSlotIndices;
}

TArray<int32> UStorageComponent::FindEmptySlots() const
{
	TArray<int32> FoundSlotIndices;
	for (int32 i = 0; i < ItemSlotList.Num(); i++) {
		if (!IsValid(ItemSlotList[i])) {
			FoundSlotIndices.Add(i);
		}
	}
	return FoundSlotIndices;
}

bool UStorageComponent::IsAllowedType(const TSubclassOf<UDataAsset> StaticData) const {
	if (AllowedItemTypes.Num() == 0) return true;
	return WhitelistAllowedTypes && AllowedItemTypes.Contains(StaticData);
}

void UStorageComponent::ClearSlot(int32 SlotIndex) {
	if (ItemSlotList.IsValidIndex(SlotIndex)) ItemSlotList[SlotIndex] = nullptr;
}

uint8 UStorageComponent::TransferItemToStorage_Implementation(UItemData* ItemDataToAdd, int32& Remaining)
{
	if (!IsValid(ItemDataToAdd)) return (uint8)EError::INVALID;
	if (!ItemDataToAdd->IsValidData()) return (uint8)EError::INVALID;
	if (!IsAllowedType(ItemDataToAdd->GetStaticDataClassGeneric())) return  (uint8)EError::NOTWHITELISTED;
	if (ItemDataToAdd->GetAmount() == 0) return (uint8)EError::INVALID;
	int32 StackSize = ItemDataToAdd->GetStackSize();
	int32 ErrCode = 0;
	Remaining = ItemDataToAdd->GetAmount();
	TArray<int32> AvailableSlots = FindMatchingSlots(ItemDataToAdd);
	if (Remaining > 0) {
		// Try to fill out existing slots first.
		if (AvailableSlots.Num() > 0) {
			for (int i = 0; i < AvailableSlots.Num(); i++) {
				ErrCode = ItemSlotList[AvailableSlots[i]]->FillAmountFromData(ItemDataToAdd, Remaining);
				if (Remaining == 0){
					break;
				}
			}
		}
		// Then fill out empty slots.
		if (Remaining > 0) {
			AvailableSlots = FindEmptySlots();
			for (int i = 0; i < AvailableSlots.Num(); i++) {
				if (Remaining > StackSize) {
					UItemData* NewData = NewObject<UItemData>(this);
					NewData->SetupFromData(StackSize, ItemDataToAdd);
					ItemSlotList[AvailableSlots[i]] = NewData;
					Remaining = Remaining - StackSize;
					ItemDataToAdd->SetAmount(Remaining);
				}
				else {
					ItemDataToAdd->Rename(nullptr, this);
					ItemSlotList[AvailableSlots[i]] = ItemDataToAdd;
					Remaining = 0;
				}
			}
		}
	}
	else {
		if(AvailableSlots.Num() == 0) return (uint8)EError::INVALID;
		// Remove items from the inventory
		for (int i = AvailableSlots.Num() - 1; i >= 0; i--) {
			ErrCode = ItemSlotList[AvailableSlots[i]]->FillAmountFromData(ItemDataToAdd, Remaining);
			if (Remaining == 0) {
				break;
			}
		}
	}
	return (uint8)(Remaining == 0);
}

uint8 UStorageComponent::AddItemToStorage_Implementation(int32 Amount, TSubclassOf<UDataAsset> StaticData, int32& Remaining)
{
	if (Amount == 0) return (uint8)EError::INVALID;
	if (!IsValid(StaticData)) return (uint8)EError::INVALID;
	if (!IsAllowedType(StaticData)) return  (uint8)EError::NOTWHITELISTED;
	UItemData* NewItemData = NewObject<UItemData>(this);
	NewItemData->SetupFromAsset(Amount, StaticData);
	int32 ErrCode = TransferItemToStorage(NewItemData, Remaining);
	return (uint8)(Remaining == 0);
}


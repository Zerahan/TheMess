// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/ItemData.h"
#include "Data/ItemStaticDataAsset.h"

#ifndef ERR_INVALID
#define ERR_INVALID = (uint8)2;
#endif

UItemData::UItemData()
	: Super()
{
	Amount		= 0;
	StaticData	= nullptr;
}

UItemData::UItemData(int32 NewAmount, TSubclassOf<UItemStaticDataAsset> NewStaticData)
{
	Amount		= NewAmount;
	StaticData	= NewStaticData;
}

void UItemData::SetupFromData(const int32 NewAmount, const UItemData* FromData) {
	SetAmount(NewAmount);
	SetStaticData(FromData->GetStaticDataClass());
}

void UItemData::SetupFromAsset(const int32 NewAmount, TSubclassOf<UDataAsset> FromAsset) {
	if (FromAsset->IsChildOf(UItemStaticDataAsset::StaticClass())) {
		StaticData = FromAsset;
		Amount = NewAmount;
	}
}

bool UItemData::IsValidData() const {
	return IsValid(StaticData);
}

int32 UItemData::GetAmount() const { return Amount; }

int32 UItemData::GetStackSize() const {
	return GetStaticData()->GetStackSize();
}

UItemStaticDataAsset* UItemData::GetStaticData() const { return StaticData->GetDefaultObject<UItemStaticDataAsset>(); }

TSubclassOf<UItemStaticDataAsset> UItemData::GetStaticDataClass() const { return StaticData; }

inline TSubclassOf<UDataAsset> UItemData::GetStaticDataClassGeneric() const {
	return StaticData;
}

int32 UItemData::SetAmount(const int32 NewAmount, const bool ModifyAmount) {
	Amount = (ModifyAmount ? Amount + NewAmount : NewAmount);
	return Amount;
}

UItemStaticDataAsset* UItemData::SetStaticData(TSubclassOf<UItemStaticDataAsset> NewStaticData) {
	StaticData = NewStaticData;
	return StaticData->GetDefaultObject<UItemStaticDataAsset>();
}

bool UItemData::IsEqual(const UItemData* ItemDataToCheck) const {
	if (!IsValid(ItemDataToCheck)) return false;
	if (!ItemDataToCheck->IsValidData()) return false;
	return StaticData == ItemDataToCheck->GetStaticDataClass();
}

uint8 UItemData::FillAmountFromData(UItemData* FromData, int32& Remaining){
	if (!IsValid(FromData)) return (uint8)EError::INVALID;
	if (!FromData->IsValidData()) return (uint8)EError::INVALID;
	if (!IsEqual(FromData)) return (uint8)EError::INVALID;
	int32 StackSize = GetStackSize();
	Remaining = 0;
	if (FromData->GetAmount() > 0) {
		if (Amount < StackSize) {
			if (FromData->GetAmount() <= StackSize - Amount) {
				SetAmount(FromData->GetAmount(), true);
				Remaining = 0;
				FromData->SetAmount(0);
			}
			else {
				Remaining = FromData->GetAmount() - (StackSize - Amount);
				SetAmount(StackSize);
				FromData->SetAmount(Remaining);
			}
		}
		else {
			Remaining = FromData->GetAmount();
		}
	}
	else {
		if(Amount > 0){
			if (Amount + FromData->GetAmount() >= 0) {
				SetAmount(Amount + FromData->GetAmount());
				Remaining = 0;
				FromData->SetAmount(0);
			}
			else {
				Remaining = FromData->GetAmount() + Amount;
				SetAmount(0);
				FromData->SetAmount(Remaining);
			}
		}
		else {
			Remaining = FromData->GetAmount();
		}
	}

	return (uint8)(Remaining == 0);
}

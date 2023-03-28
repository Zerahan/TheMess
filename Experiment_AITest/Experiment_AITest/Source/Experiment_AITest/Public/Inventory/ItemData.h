// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Globals.h"
#include "UObject/NoExportTypes.h"
#include "ItemData.generated.h"

class UItemStaticDataAsset;

/**
 * 
 */
UCLASS(BlueprintType)
class EXPERIMENT_AITEST_API UItemData : public UObject
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, BlueprintGetter = GetAmount, meta = (AllowPrivateAccess = "true"))
	int32 Amount;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, BlueprintGetter = GetStaticDataClass, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UItemStaticDataAsset> StaticData;

public:
	UItemData();
	UItemData(int32 NewAmount, TSubclassOf<UItemStaticDataAsset> NewStaticData);

	UFUNCTION(BlueprintCallable)
	void SetupFromData(const int32 NewAmount, const UItemData* FromData);

	UFUNCTION(BlueprintCallable)
	void SetupFromAsset(const int32 NewAmount, TSubclassOf<UDataAsset> FromAsset);
	
	UFUNCTION(BlueprintCallable)
	bool IsValidData() const;

	UFUNCTION(BlueprintCallable)
	int32 GetAmount() const;

	UFUNCTION(BlueprintCallable)
	int32 GetStackSize() const;

	UFUNCTION(BlueprintCallable)
	UItemStaticDataAsset* GetStaticData() const;

	UFUNCTION(BlueprintCallable)
	TSubclassOf<UItemStaticDataAsset> GetStaticDataClass() const;

	UFUNCTION(BlueprintCallable)
	TSubclassOf<UDataAsset> GetStaticDataClassGeneric() const;
	
	UFUNCTION(BlueprintCallable)
	int32 SetAmount(const int32 NewAmount, const bool ModifyAmount = false);

	UFUNCTION(BlueprintCallable)
	UItemStaticDataAsset* SetStaticData(const TSubclassOf<UItemStaticDataAsset> NewStaticData);

	UFUNCTION(BlueprintCallable)
	uint8 FillAmountFromData(UItemData* FromData, int32& Remaining);

	UFUNCTION(BlueprintCallable)
	bool IsEqual(const UItemData* ItemDataToCheck) const;
};

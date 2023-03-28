// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Globals.h"
#include "Components/ActorComponent.h"
#include "StorageComponent.generated.h"

class UItemData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXPERIMENT_AITEST_API UStorageComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, meta = (AllowPrivateAccess = "true"))
	TArray<UItemData*> ItemSlotList;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	int32 MaxSlotCount;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UDataAsset>> AllowedItemTypes;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	bool WhitelistAllowedTypes;
	
public:	
	// Sets default values for this component's properties
	UStorageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	TArray<int32> FindMatchingSlots(const UItemData* ItemData, const bool IncludeEmpty = false) const;

	UFUNCTION(BlueprintCallable)
	TArray<int32> FindEmptySlots() const;

	UFUNCTION(BlueprintCallable)
	bool IsAllowedType(const TSubclassOf<UDataAsset> StaticData) const;

	void ClearSlot(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	uint8 TransferItemToStorage(UItemData* ItemDataToAdd, int32& Remaining);
	virtual uint8 TransferItemToStorage_Implementation(UItemData* ItemDataToAdd, int32& Remaining);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	uint8 AddItemToStorage(int32 Amount, TSubclassOf<UDataAsset> StaticData, int32& Remaining);
	virtual uint8 AddItemToStorage_Implementation(int32 Amount, TSubclassOf<UDataAsset> StaticData, int32& Remaining);
	
};

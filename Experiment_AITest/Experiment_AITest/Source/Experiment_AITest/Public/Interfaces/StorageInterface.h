// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Globals.h"
#include "UObject/Interface.h"
#include "StorageInterface.generated.h"

class UItemData;
class UStorageComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UStorageInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class EXPERIMENT_AITEST_API IStorageInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UStorageComponent* GetStorageComponent() const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	uint8 TransferItemToStorage(UItemData* ItemDataToAdd, int32& Remaining);
	virtual uint8 TransferItemToStorage_Implementation(UItemData* ItemDataToAdd, int32& Remaining);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	uint8 AddItemToStorage(int32 Amount, TSubclassOf<UDataAsset> StaticData, int32& Remaining);
	virtual uint8 AddItemToStorage_Implementation(int32 Amount, TSubclassOf<UDataAsset> StaticData, int32& Remaining);


};

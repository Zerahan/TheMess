// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/AICharacter_Basic.h"
//#include "Interfaces/StorageInterface.h"
#include "WorkerCharacter_Basic.generated.h"

class AWorkableBuilding_Basic;
//class UStorageComponent;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class EXPERIMENT_AITEST_API AWorkerCharacter_Basic : public AAICharacter_Basic// , public IStorageInterface
{
	GENERATED_BODY()

	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	//UStorageComponent* StorageComponent;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, meta = (AllowPrivateAccess = "true"))
	AWorkableBuilding_Basic* AssignedWorksite;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AWorkableBuilding_Basic>> ValidWorksiteClasses;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, meta = (AllowPrivateAccess = "true"))
	AWorkableBuilding_Basic* AssignedHouse;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AWorkableBuilding_Basic>> ValidHouseClasses;

public:
	AWorkerCharacter_Basic();

	UFUNCTION(BlueprintCallable)
	bool SetupAssignments();

	UFUNCTION(BlueprintCallable)
	AWorkableBuilding_Basic* GetAssignedWorksite() const;

	UFUNCTION(BlueprintCallable)
	AWorkableBuilding_Basic* GetAssignedHouse() const;

	//virtual UStorageComponent* GetStorageComponent_Implementation() const override;
	//virtual uint8 TransferItemToStorage_Implementation(UItemData* ItemDataToAdd, int32& Remaining) override;
	//virtual uint8 AddItemToStorage_Implementation(int32 Amount, TSubclassOf<UDataAsset> StaticData, int32& Remaining) override;
};

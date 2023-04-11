// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Buildings/WorkerAITypes.h"
#include "BuildingDataAsset.generated.h"

class UItemData;

USTRUCT(BlueprintType)
struct EXPERIMENT_AITEST_API FWorkData {
	GENERATED_BODY()

public:
	FWorkData()
		: WorkType(EWorkType::W_Undefined)
	{};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EWorkType WorkType;
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class EXPERIMENT_AITEST_API UBuildingDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UBuildingDataAsset()
		: DisplayName(FText::FromString("Undefined"))
		, TileSnapSize(2)
	{}

	/** Type of this item, set in native parent class */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	FPrimaryAssetType ItemType;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText DisplayName;

	UFUNCTION(BlueprintCallable)
	FText GetDisplayName() const { return DisplayName; }

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSoftObjectPtr<UTexture2D> Icon;

	UFUNCTION(BlueprintCallable)
	UTexture2D* GetIcon() const;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TMap<EWorkType, FWorkData> WorkInfo;

	UFUNCTION(BlueprintCallable)
	TMap<EWorkType, FWorkData> GetWorkInfo() const { return WorkInfo; }

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 TileSnapSize;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<class ABuilding_Basic> SpawnedBuildingClass;

	UFUNCTION(BlueprintCallable)
	bool IsValidWorkType(EWorkType WorkType) const;

	UFUNCTION(BlueprintCallable)
	void DoProduction(AActor* ParentActor, EWorkType WorkType) const;

	UFUNCTION(BlueprintCallable)
	TArray<TSubclassOf<UDataAsset>> GetProduction(EWorkType WorkType) const;


	
	UFUNCTION(BlueprintCallable)
	FString GetIdentifierString() const;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};

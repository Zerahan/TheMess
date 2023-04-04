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
UCLASS(BlueprintType, Blueprintable, Abstract)
class EXPERIMENT_AITEST_API UBuildingDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, BlueprintGetter = GetDisplayName, meta = (AllowPrivateAccess = "true"))
	FText DisplayName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TMap<EWorkType, FWorkData> WorkInfo;

public:
	UBuildingDataAsset();

	UFUNCTION(BlueprintCallable)
	FText GetDisplayName() const { return DisplayName; }
	
	UFUNCTION(BlueprintCallable)
	bool IsValidWorkType(EWorkType WorkType) const;

	UFUNCTION(BlueprintCallable)
	void DoProduction(AActor* ParentActor, EWorkType WorkType) const;

	UFUNCTION(BlueprintCallable)
	TArray<TSubclassOf<UDataAsset>> GetProduction(EWorkType WorkType) const;

	UFUNCTION(BlueprintCallable)
	TMap<EWorkType, FWorkData> GetWorkInfo() const;
};

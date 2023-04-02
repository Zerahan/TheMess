// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemTypes.generated.h"

/**
 * 
 */
class UItemStaticDataAsset;

USTRUCT(BlueprintType)
struct EXPERIMENT_AITEST_API FItemData_Struct
{
	GENERATED_BODY()

public:
	FItemData_Struct()
		: Amount(0)
		, StaticData(nullptr)
	{};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 Amount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UItemStaticDataAsset> StaticData;
};

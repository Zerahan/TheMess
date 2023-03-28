// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemStaticDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class EXPERIMENT_AITEST_API UItemStaticDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, BlueprintGetter=GetDisplayName, meta = (AllowPrivateAccess = "true"))
	FName DisplayName;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UTexture> Icon;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, BlueprintGetter = GetStackSize, meta = (AllowPrivateAccess = "true"))
	int32 StackSize;
	
public:
	UItemStaticDataAsset();

	UFUNCTION(BlueprintCallable)
	bool IsValidAsset() const;

	UFUNCTION(BlueprintCallable)
	FName GetDisplayName() const;

	UFUNCTION(BlueprintCallable)
	UTexture* GetIcon() const;

	UFUNCTION(BlueprintCallable)
	int32 GetStackSize() const;
};

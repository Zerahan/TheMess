// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TileObject.generated.h"

class UTileDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTileCollapsed, int32, x, int32, y);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTileDataChanged, int32, x, int32, y);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AGORA_API UTileObject : public UObject
{
	GENERATED_BODY()

	UPROPERTY();
	FIntVector Location;
	
	UPROPERTY()
	bool IsCollapsed;

	UPROPERTY()
	TArray<TSubclassOf<UTileDataAsset>> PossibleTileTypes;
	
public:
	UTileObject();

	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Setup(const FIntVector NewLocation, const TArray<TSubclassOf<UTileDataAsset>>& NewPossibleTileTypes);
	virtual void Setup_Implementation(const FIntVector NewLocation, const TArray<TSubclassOf<UTileDataAsset>>& NewPossibleTileTypes);

	UFUNCTION(BlueprintCallable)
	bool GetIsCollapsed() const;
	
	UFUNCTION(BlueprintCallable)
	FIntVector GetTileLocation() const;

	UFUNCTION(BlueprintCallable)
	TArray<TSubclassOf<UTileDataAsset>> GetPossibleTileTypes() const;

	UFUNCTION(BlueprintCallable)
	int32 GetPossibleTileCount() const;
	
	/*
	*	Reduces the possibility space to exactly 1 by randomly picking a single possible option.
	*	@return	Returns true if the tile's data has changed.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CollapseTile();
	virtual bool CollapseTile_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool ShrinkPossibleTileTypes(const TArray<UTileObject*>& NeighborTiles);
	virtual bool ShrinkPossibleTileTypes_Implementation(const TArray<UTileObject*>& NeighborTiles);

	UPROPERTY(BlueprintAssignable)
	FOnTileCollapsed OnTileCollapsed;

	UPROPERTY(BlueprintAssignable)
	FOnTileCollapsed OnTileDataChanged;
};

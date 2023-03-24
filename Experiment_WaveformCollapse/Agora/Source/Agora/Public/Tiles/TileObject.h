// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TileObject.generated.h"

class UTileDataAsset;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AGORA_API UTileObject : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	bool IsCollapsed;

	UPROPERTY()
	TArray<TSubclassOf<UTileDataAsset>> PossibleTileTypes;
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Setup(TArray<TSubclassOf<UTileDataAsset>>& NewPossibleTileTypes);
	virtual void Setup_Implementation(TArray<TSubclassOf<UTileDataAsset>>& NewPossibleTileTypes);

	UFUNCTION(BlueprintCallable)
	bool GetIsCollapsed() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CollapseTile();
	virtual bool CollapseTile_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool ShrinkTile(const TArray<UTileObject*>& NeighborTiles);
	virtual bool ShrinkTile_Implementation(const TArray<UTileObject*>& NeighborTiles);
};

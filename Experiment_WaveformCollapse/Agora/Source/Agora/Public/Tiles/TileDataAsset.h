// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PaperTileLayer.h"
#include "TileDataAsset.generated.h"

class UTileObject;

UENUM(BlueprintType)
enum class EMapLayer : uint8
{
	L_Grid				UMETA(DisplayName = "Grid"),
	L_Sky				UMETA(DisplayName = "Sky"),
	L_Buildings			UMETA(DisplayName = "Buildings"),
	L_TerrainOverlayB	UMETA(DisplayName = "TerrainOverlayB"),
	L_TerrainOverlayA	UMETA(DisplayName = "TerrainOverlayA"),
	L_TerrainOverride	UMETA(DisplayName = "TerrainOverride"),
	L_Terrain			UMETA(DisplayName = "Terrain"),
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class AGORA_API UTileDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TMap<EMapLayer, FPaperTileInfo> Graphic;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<TSubclassOf<UTileDataAsset>> PossibleNeighbors;

	UFUNCTION(BlueprintCallable)
	TMap<EMapLayer, FPaperTileInfo> GetGraphic() const;

	UFUNCTION(BlueprintCallable)
	TArray<TSubclassOf<UTileDataAsset>> GetPossibleNeighbors() const;

	UFUNCTION(BlueprintCallable)
	bool IsPossibleWithNeighbors(const TArray<TSubclassOf<UTileDataAsset>>& PossibilitySpace, const TArray<TSubclassOf<UTileDataAsset>>& CollapsedPossibilities) const;
};

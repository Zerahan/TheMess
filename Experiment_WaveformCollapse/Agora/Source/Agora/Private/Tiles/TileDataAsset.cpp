// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiles/TileObject.h"
#include "Tiles/TileDataAsset.h"

TMap<EMapLayer, FPaperTileInfo> UTileDataAsset::GetGraphic() const { return Graphic; }

TArray<TSubclassOf<UTileDataAsset>> UTileDataAsset::GetPossibleNeighbors() const { return PossibleNeighbors; }

bool UTileDataAsset::IsPossibleWithNeighbors(const TArray<TSubclassOf<UTileDataAsset>>& PossibilitySpace, const TArray<TSubclassOf<UTileDataAsset>>& CollapsedPossibilities) const
{
	// Already-collapsed tiles outright block if an invalid type is next to them.
	for (auto Data : CollapsedPossibilities) {
		if (!PossibleNeighbors.Contains(Data)) {
			return false;
		}
	}
	// Uncollapsed tiles reduce
	bool ContainsInvalid = false;
	for (auto Data : PossibleNeighbors) {
		if (!PossibilitySpace.Contains(Data)) {
			ContainsInvalid = true;
			break;
		}
	}
	return !ContainsInvalid;
}

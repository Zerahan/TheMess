// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiles/TileObject.h"
#include "Tiles/TileDataAsset.h"

void UTileObject::Setup_Implementation(TArray<TSubclassOf<UTileDataAsset>>& NewPossibleTileTypes)
{
	PossibleTileTypes = NewPossibleTileTypes;
}

bool UTileObject::GetIsCollapsed() const { return IsCollapsed; }

bool UTileObject::CollapseTile_Implementation()
{
	return false;
}

bool UTileObject::ShrinkTile_Implementation(const TArray<UTileObject*>& NeighborTiles)
{
	return false;
}

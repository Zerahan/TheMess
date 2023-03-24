// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiles/TileObject.h"
#include "Tiles/TileDataAsset.h"

UTileObject::UTileObject()
{
	IsCollapsed = false;
}

void UTileObject::BeginDestroy()
{
	//OnTileCollapsed.RemoveAll(this);
	//OnTileDataChanged.RemoveAll(this);
	Super::BeginDestroy();
}

void UTileObject::Setup_Implementation(const FIntVector NewLocation, const TArray<TSubclassOf<UTileDataAsset>>& NewPossibleTileTypes)
{
	Location = NewLocation;
	PossibleTileTypes = NewPossibleTileTypes;
}

bool UTileObject::GetIsCollapsed() const { return IsCollapsed; }

FIntVector UTileObject::GetTileLocation() const { return Location; }

TArray<TSubclassOf<UTileDataAsset>> UTileObject::GetPossibleTileTypes() const { return PossibleTileTypes; }

int32 UTileObject::GetPossibleTileCount() const { return PossibleTileTypes.Num(); }

bool UTileObject::CollapseTile_Implementation()
{
	if (GetIsCollapsed()) return false;
	IsCollapsed = true;
	
	if (PossibleTileTypes.Num() == 0) {
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("ERROR: Tile(%i,%i) has no possible types!"), Location.X, Location.Y));
		return false;
	}
	TSubclassOf<UTileDataAsset> ChosenClass = PossibleTileTypes[FMath::RandRange(0, PossibleTileTypes.Num() - 1)];
	PossibleTileTypes.Empty();
	PossibleTileTypes.Add(ChosenClass);

	OnTileCollapsed.Broadcast(Location.X, Location.Y);
	return true;
}

bool UTileObject::ShrinkPossibleTileTypes_Implementation(const TArray<UTileObject*>& NeighborTiles)
{
	if (GetIsCollapsed()) return false;
	bool DataChanged = false;
	if (PossibleTileTypes.Num() > 1) {
		TArray<TSubclassOf<UTileDataAsset>> PossibleNeighbors;
		TArray<TSubclassOf<UTileDataAsset>> CollapsedNeighbors;
		for (UTileObject* Neighbor : NeighborTiles) {
			if (!Neighbor->GetIsCollapsed()) {
				TArray<TSubclassOf<UTileDataAsset>> Temp = Neighbor->GetPossibleTileTypes();
				for (TSubclassOf<UTileDataAsset> Data : Temp) {
					PossibleNeighbors.AddUnique(Data);
				}
			}
			else {
				TArray<TSubclassOf<UTileDataAsset>> Temp = Neighbor->GetPossibleTileTypes();
				for (TSubclassOf<UTileDataAsset> Data : Temp) {
					CollapsedNeighbors.AddUnique(Data);
				}
			}
		}
		for (int32 i = PossibleTileTypes.Num() - 1; i >= 0; i--) {
			if (!PossibleTileTypes[i].GetDefaultObject()->IsPossibleWithNeighbors(PossibleNeighbors, CollapsedNeighbors)) {
				PossibleTileTypes.RemoveAt(i);
				DataChanged = true;
			}
		}
	}
	if (PossibleTileTypes.Num() <= 1) {
		CollapseTile();
		return true;
	}
	OnTileDataChanged.Broadcast(Location.X, Location.Y);
	return DataChanged;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiles/CollapseHandlerComponent.h"
#include "Tiles/TileObject.h"
#include "PaperTileMapActor.h"
#include "PaperTileMapComponent.h"
#include "PaperTileMap.h"
#include "PaperTileLayer.h"

// Sets default values for this component's properties
UCollapseHandlerComponent::UCollapseHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MapWidth	= 0;
	MapHeight	= 0;
	MapDepth	= 0;

	IsSetup		= false;

	IsCollapseStarted = false;

	// ...
}


// Called when the game starts
void UCollapseHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCollapseHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCollapseHandlerComponent::Setup(UPaperTileMapComponent* TileMap)
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "Setting up...");
	if (!IsValid(TileMap)) {
		IsSetup		= false;
		TileMapRef	= nullptr;
		MapWidth	= 0;
		MapHeight	= 0;
		MapDepth	= 0;
		MapTiles.Empty();
		return;
	}
	TileMapRef = TileMap;
	TileMapRef->GetMapSize(MapWidth, MapHeight, MapDepth);
	MapTiles.Empty();
	if (MapWidth > 0 && MapHeight > 0) {
		for (int32 Y = 0; Y < MapHeight; Y++) {
			for (int32 X = 0; X < MapWidth; X++) {
				MapTiles.Add(NewObject<UTileObject>(this));
				int32 i = Y * MapWidth + X;
				if (MapTiles.IsValidIndex(i)) {
					MapTiles[i]->Setup(FIntVector(X, Y, 0), AvailableTiles);
					MapTiles[i]->OnTileCollapsed.AddDynamic(this, &UCollapseHandlerComponent::OnTileCollapsed);
					MapTiles[i]->OnTileDataChanged.AddDynamic(this, &UCollapseHandlerComponent::OnTileDataChanged);
					UE_LOG(LogTemp, Warning, TEXT("Tile %i @ %i,%i"), i, X, Y);
				}
			}
		}
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Setup Complete: %i x %i"), MapWidth, MapHeight));
		IsSetup = true;
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "Setup Failed");
	IsSetup = false;
}

void UCollapseHandlerComponent::NextFrame_Implementation()
{
	if(!IsSetup) return;
	UTileObject* SmallestTile = MapTiles[0];
	switch (CollapseMethod) {
		case ECollapseMethod::C_SmallestFirstC:
			if (!IsCollapseStarted) {
				SmallestTile = MapTiles[MapTiles.Num()/2];
			}
			else {
				for (auto* Tile : MapTiles) {
					if (!Tile->GetIsCollapsed() && Tile->GetPossibleTileCount() <= SmallestTile->GetPossibleTileCount()) {
						SmallestTile = Tile;
					}
				}
			}
			break;
		case ECollapseMethod::C_SmallestFirst:
			for (auto* Tile : MapTiles) {
				if (!Tile->GetIsCollapsed() && Tile->GetPossibleTileCount() <= SmallestTile->GetPossibleTileCount()) {
					SmallestTile = Tile;
				}
			}
			break;
		case ECollapseMethod::C_HorizontalScanLR:
			if (IsCollapseStarted) {
				FIntVector Location = LastCollapsedTile->GetTileLocation();
				int32 TileIndex = (Location.Y * MapWidth + Location.X) + 1;
				if (!MapTiles.IsValidIndex(TileIndex)) return;
				SmallestTile = MapTiles[TileIndex];
				//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Cell: %i, %i @ %i"), SmallestTile->GetTileLocation().X, SmallestTile->GetTileLocation().Y, TileIndex));
			}
			break;
		case ECollapseMethod::C_HorizontalScanRL:
			if (!IsCollapseStarted) {
				SmallestTile = MapTiles.Last();
			}else{
				FIntVector Location = LastCollapsedTile->GetTileLocation();
				int32 TileIndex = (Location.Y * MapWidth + Location.X) - 1;
				if (!MapTiles.IsValidIndex(TileIndex)) return;
				SmallestTile = MapTiles[TileIndex];
			}
			break;
		case ECollapseMethod::C_VerticalScanTB:
			// Todo
			break;
		case ECollapseMethod::C_VerticalScanBT:
			// Todo
			break;
		default:
			break;
	}
	IsCollapseStarted = true;
	LastCollapsedTile = SmallestTile;
	LastCollapsedTile->CollapseTile();
	
	// All of this just propagates the collapsed tile's reduced possibility space to all neighbors, and all neighbors of neighbors.
	FIntVector Location = LastCollapsedTile->GetTileLocation();
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Cell: %i, %i"), Location.X, Location.Y));
	TArray<UTileObject*> OpenList = GetNeighbors(Location.X, Location.Y);
	GEngine->AddOnScreenDebugMessage(-1,10,FColor::Red, FString::Printf(TEXT("Number of neighbors: %i"), OpenList.Num()));
	TArray<UTileObject*> ClosedList = { LastCollapsedTile };
	TArray<UTileObject*> NextNeighbors;
	UTileObject* ThisTile;
	int32 Count = 0;
	while (OpenList.Num() > 0 && Count++ < MapTiles.Num()) {
		ThisTile = OpenList[0];
		OpenList.RemoveAt(0);
		ClosedList.Add(ThisTile);
		NextNeighbors.Empty();
		Location = ThisTile->GetTileLocation();
		NextNeighbors = GetNeighbors(Location.X, Location.Y);
		if(ThisTile->GetIsCollapsed()) continue;
		if (ThisTile->ShrinkPossibleTileTypes(NextNeighbors)) {
			for (auto* Tile : NextNeighbors) {
				if (OpenList.Contains(Tile) || ClosedList.Contains(Tile)) continue;
				OpenList.Add(Tile);
			}
		}
	}
}

TArray<UTileObject*> UCollapseHandlerComponent::GetNeighbors_Implementation(int32 x, int32 y) const
{
	TArray<UTileObject*> FoundNeighbors;
	int32 locX, locY, idx;
	for (int32 tileY = -1; tileY <= 1; tileY++) {
		locY = y + tileY;
		if (locY < 0 || locY >= MapHeight) continue;	// Y can't be out of bounds.
		for (int32 tileX = -1; tileX <= 1; tileX++) {
			if(tileX == 0 && tileY == 0) continue;			// Can't be a neighbor of itself.
			locX = x + tileX;
			if (locX < 0 || locX >= MapWidth) continue;			// X can't be out of bounds.
			idx = (locY * MapWidth) + locX;					// Convert the 2d coord to 1d.
			if (!MapTiles.IsValidIndex(idx)) continue;		// Has to be a valid index.
			FoundNeighbors.Add(MapTiles[idx]);
		}
	}
	return FoundNeighbors;
}

void UCollapseHandlerComponent::SetTileFromGraphicArray(int32 TileIndex, TMap<EMapLayer, FPaperTileInfo>& Graphics)
{
	if(!MapTiles.IsValidIndex(TileIndex)) return;
	FIntVector Location = MapTiles[TileIndex]->GetTileLocation();
	TArray<EMapLayer> Keys;
	Graphics.GetKeys(Keys);
	for (auto Key : Keys) {
		TileMapRef->SetTile(Location.X, Location.Y, (int32)Key, Graphics[Key]);
	}
}

void UCollapseHandlerComponent::OnTileCollapsed_Implementation(int32 X, int32 Y)
{
	int32 TileIndex = Y * MapWidth + X;
	if (!MapTiles.IsValidIndex(TileIndex)) return;
	TMap<EMapLayer, FPaperTileInfo> Graphics = MapTiles[TileIndex]->GetPossibleTileTypes()[0].GetDefaultObject()->GetGraphic();
	SetTileFromGraphicArray(TileIndex, Graphics);
}

void UCollapseHandlerComponent::OnTileDataChanged_Implementation(int32 X, int32 Y)
{
	int32 TileIndex = Y * MapWidth + X;
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Cell: %i, %i @ %i"), X, Y, NumberTilesInfo.PackedTileIndex));
	if (!MapTiles.IsValidIndex(TileIndex)) return;
	NumberTilesInfo.PackedTileIndex = FMath::Clamp(MapTiles[TileIndex]->GetPossibleTileCount(), 0, 8);
	TMap<EMapLayer, FPaperTileInfo> Graphics;
	Graphics.Add(EMapLayer::L_Terrain, NumberTilesInfo);
	SetTileFromGraphicArray(TileIndex, Graphics);
}


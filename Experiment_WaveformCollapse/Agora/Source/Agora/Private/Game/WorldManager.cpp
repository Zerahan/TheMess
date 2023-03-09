// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/WorldManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BillboardComponent.h"
#include "Components/ArrowComponent.h"
#include "PaperTileMapActor.h"
#include "PaperTileMapComponent.h"
#include "PaperTileMap.h"
#include "PaperTileLayer.h"

// Sets default values
AWorldManager::AWorldManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WorldBoundingBox = FBox(FVector(-1, -1, -10), FVector(1, 1, 10));

#if WITH_EDITORONLY_DATA
	BillboardComponent = CreateEditorOnlyDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));

	if (!IsRunningCommandlet())
	{
		// Structure to hold one-time initialization
		struct FConstructorStatics
		{
			ConstructorHelpers::FObjectFinderOptional<UTexture2D> WorldManagerTextureObject;
			FName ID_WorldManager;
			FText NAME_WorldManager;
			FName ID_Navigation;
			FText NAME_Navigation;
			FConstructorStatics()
				: WorldManagerTextureObject(TEXT("/Engine/EditorResources/S_Terrain"))
				, ID_WorldManager(TEXT("WorldManager"))
				, NAME_WorldManager(NSLOCTEXT("SpriteCategory", "WorldManager", "World Manager"))
				, ID_Navigation(TEXT("Navigation"))
				, NAME_Navigation(NSLOCTEXT("SpriteCategory", "Navigation", "Navigation"))
			{
			}
		};
		static FConstructorStatics ConstructorStatics;

		if (BillboardComponent) {
			BillboardComponent->Sprite = ConstructorStatics.WorldManagerTextureObject.Get();
			BillboardComponent->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
			BillboardComponent->SpriteInfo.Category = ConstructorStatics.ID_WorldManager;
			BillboardComponent->SpriteInfo.DisplayName = ConstructorStatics.NAME_WorldManager;
		}

		if (ArrowComponent)
		{
			ArrowComponent->ArrowColor = FColor(150, 200, 255);

			ArrowComponent->ArrowSize = 1.0f;
			ArrowComponent->bTreatAsASprite = true;
			ArrowComponent->SpriteInfo.Category = ConstructorStatics.ID_Navigation;
			ArrowComponent->SpriteInfo.DisplayName = ConstructorStatics.NAME_Navigation;
			ArrowComponent->SetupAttachment(RootComponent);
			ArrowComponent->bIsScreenSizeScaled = true;
		}
	}
#endif // WITH_EDITORONLY_DATA
}

void AWorldManager::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	Super::PostEditChangeProperty(e);
	FName PropertyName = (e.Property != NULL ? e.Property->GetFName() : NAME_None);
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AWorldManager, TileMapActorRef) || PropertyName == GET_MEMBER_NAME_CHECKED(AWorldManager, RefreshTileMap)) {
		RefreshTileMap = false;
		RecalculateWorld();
	}
}

int32 AWorldManager::IsInBoundsX(FVector Location) const
{
	if (Location.X >= WorldBoundingBox.Max.X) {
		return 1;
	}
	if (Location.X <= WorldBoundingBox.Min.X) {
		return -1;
	}
	return 0;
}

int32 AWorldManager::IsInBoundsY(FVector Location) const
{
	if (Location.Y >= WorldBoundingBox.Max.Y) {
		return 1;
	}
	if (Location.Y <= WorldBoundingBox.Min.Y) {
		return -1;
	}
	return 0;
}

FVector2D AWorldManager::GetGridSize() const
{
	if (!IsValid(TileMapRef)) { return FVector2D(-1.f,-1.f); }
	return FVector2D(TileMapRef->MapWidth, TileMapRef->MapHeight);
}

FVector AWorldManager::ClampToBounds(FVector Location)
{
	Location.Z = 0;
	if (!WorldBoundingBox.IsInside(Location)) {
		Location.X = FMath::Clamp(Location.X, WorldBoundingBox.Min.X, WorldBoundingBox.Max.X);
		Location.Y = FMath::Clamp(Location.Y, WorldBoundingBox.Min.Y, WorldBoundingBox.Max.Y);
	}
	return Location;
}

void AWorldManager::RecalculateWorld()
{
	if (IsValid(TileMapActorRef)) {
		TileMapComponentRef = TileMapActorRef->FindComponentByClass<UPaperTileMapComponent>();
		if (!IsValid(TileMapComponentRef)) { return; }
		TileMapRef = TileMapComponentRef->TileMap;
		if (!IsValid(TileMapRef)) { return; }
		FVector2D MapDimensions = FVector2D(TileMapRef->MapWidth * TileMapRef->TileWidth, TileMapRef->MapHeight * TileMapRef->TileHeight);
		FVector2D MapDimensions_Offset = FVector2D(MapDimensions.X - (TileMapRef->TileWidth), MapDimensions.Y - (TileMapRef->TileHeight));
		MapDimensions /= TileMapRef->PixelsPerUnrealUnit;
		MapDimensions_Offset /= TileMapRef->PixelsPerUnrealUnit;

		WorldBoundingBox.Min = FVector(GetActorLocation().X - MapDimensions.X / 2.f, GetActorLocation().Y - MapDimensions.Y / 2.f, -10.f);
		WorldBoundingBox.Max = FVector(GetActorLocation().X + MapDimensions.X / 2.f, GetActorLocation().Y + MapDimensions.Y / 2.f, 10.f);

		TileSizeInUnits = FVector2D(TileMapRef->TileWidth, TileMapRef->TileHeight);
		TileSizeInUnits /= TileMapRef->PixelsPerUnrealUnit;

#if WITH_EDITORONLY_DATA
		ArrowComponent->SetWorldLocation(WorldBoundingBox.Min + GetActorLocation());
		ArrowComponent->SetWorldLocation(FVector(ArrowComponent->GetComponentLocation().X, ArrowComponent->GetComponentLocation().Y, 0));
#endif // WITH_EDITORONLY_DATA
		
		TileMapActorRef->SetActorLocation(FVector(GetActorLocation().X - MapDimensions_Offset.X / 2.f, GetActorLocation().Y - MapDimensions_Offset.Y / 2.f, TileMapActorRef->GetActorLocation().Z));
	}
}

void AWorldManager::ToggleGrid()
{
	if (IsValid(TileMapComponentRef)) {
		int32 GridLayerIndex = 0;
		FLinearColor Color = TileMapComponentRef->GetLayerColor(GridLayerIndex);
		if (Color.A != 0) {
			Color.A = 0;
		}
		else {
			Color.A = 0.5f;
		}
		TileMapComponentRef->SetLayerColor(Color);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TileMapRef->TileLayers[GridLayerIndex]->LayerName.ToString() + ": " + FString::SanitizeFloat(TileMapComponentRef->GetLayerColor(GridLayerIndex).A, 2));
	}
}

FVector AWorldManager::SnapLocationToGrid(const FVector Location, bool SnapToTileCenter) const
{
	FVector SnappedLocation = FVector(
		((int)(Location.X / TileSizeInUnits.X) + (0.5f * FMath::Sign(Location.X))) * TileSizeInUnits.X,
		((int)(Location.Y / TileSizeInUnits.Y) + (0.5f * FMath::Sign(Location.Y))) * TileSizeInUnits.Y,
		0
	);
	return SnappedLocation;
}

void AWorldManager::ConvertLocationToTileIndex(const FVector Location, FVector2D& TileIndex) const
{
	FVector AdjustedLocation = Location - WorldBoundingBox.Min;
	TileIndex.X = AdjustedLocation.X / TileSizeInUnits.X;
	TileIndex.Y = AdjustedLocation.Y / TileSizeInUnits.Y;
}

void AWorldManager::ConvertTileIndexToLocation(const int32 Index, FVector& Location) const
{
	
	float X = (Index % TileMapRef->TileWidth) * TileSizeInUnits.X;
	float Y = (int)(Index / TileMapRef->TileWidth) * TileSizeInUnits.Y;
}

bool AWorldManager::GetLayerIndex(FString LayerName, int32& LayerIndex) const
{
	if (TileMapRef->IsLayerNameInUse(FText::FromString(LayerName))) {
		for (int i = 0; i < TileMapRef->TileLayers.Num(); i++) {
			if (TileMapRef->TileLayers[i]->LayerName.ToString() == LayerName) {
				LayerIndex = i;
				return true;
			}
		}
	}
	return false;
}

void AWorldManager::SetTile(const FVector2D TileIndex, const FPaperTileInfo TileInfo, int32 LayerIndex)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Tile is: " + FString::FromInt(TileMapRef->));
	TileMapComponentRef->SetTile((int32)TileIndex.X, (int32)TileIndex.Y, LayerIndex, TileInfo);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Tile changed to: ");
}

void AWorldManager::SetTileFromWorld(const FVector Location, const FPaperTileInfo TileInfo, int32 LayerIndex)
{
	if (!WorldBoundingBox.IsInsideXY(Location)) { return; }
	FVector2D TileIndex;

	ConvertLocationToTileIndex(Location, TileIndex);

	SetTile(TileIndex, TileInfo, LayerIndex);
	
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Click Location: " + FString::SanitizeFloat(TileIndex.X) + ", " + FString::FromInt(TileIndex.Y));
}

// Called when the game starts or when spawned
void AWorldManager::BeginPlay()
{
	Super::BeginPlay();
	RecalculateWorld();
}

// Called every frame
void AWorldManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
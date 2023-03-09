// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/BasicBuilding.h"
#include "Game/WorldManager.h"
#include "Kismet/GameplayStatics.h"
#include "PaperTileMap.h"
#include "PaperTileLayer.h"
#include "Components/BoxComponent.h"

// Sets default values
ABasicBuilding::ABasicBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LayerName = "Buildings";

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRootComponent"));

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetBoxExtent(FVector(15, 15, 50));
	CollisionBox->SetRelativeLocation(FVector());
	CollisionBox->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
	//CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CollisionBox->SetupAttachment(RootComponent);
}

void ABasicBuilding::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	Super::PostEditChangeProperty(e);
	FName PropertyName = (e.Property != NULL ? e.Property->GetFName() : NAME_None);
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ABasicBuilding, TileMapRef)) {
		if (TileMapRef) {
			CollisionBox->SetBoxExtent(FVector(TileMapRef->MapWidth * TileMapRef->TileWidth * 0.5f - 1, TileMapRef->MapHeight * TileMapRef->TileHeight * 0.5f - 1, 50));
			CollisionBox->SetRelativeLocation(FVector((TileMapRef->MapWidth - 1) * TileMapRef->TileWidth * 0.5f, 0 - (TileMapRef->MapHeight - 1) * TileMapRef->TileHeight * 0.5f, 0));
		}
	}
}

// Called when the game starts or when spawned
void ABasicBuilding::BeginPlay()
{
	Super::BeginPlay();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "ABasicBuilding::BeginPlay");

	WorldManagerRef = Cast<AWorldManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AWorldManager::StaticClass()));
	if (TileMapRef && IsValid(WorldManagerRef)) {
		FVector2D TileOrigin;
		WorldManagerRef->ConvertLocationToTileIndex(GetActorLocation(), TileOrigin);

		TileMapRef->MapWidth;
		TileMapRef->MapHeight;
		int32 LayerIndex;
		if (!WorldManagerRef->GetLayerIndex(LayerName, LayerIndex)) {
			UE_LOG(LogTemp, Warning, TEXT("BasicBuilding.cpp:34 attempted to get invalid layer from world: %s"), *LayerName);
			return;
		}
		for (int y = 0; y < TileMapRef->MapHeight; y++) {
			for (int x = 0; x < TileMapRef->MapWidth; x++) {
				FPaperTileInfo Info = TileMapRef->TileLayers[0]->GetCell(x,y);
				WorldManagerRef->SetTile(FVector2D(TileOrigin.X + x, TileOrigin.Y + y), Info, LayerIndex);
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Set Tile");
			}
		}
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "ABasicBuilding::BeginPlay Finished");
	}
}

// Called every frame
void ABasicBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


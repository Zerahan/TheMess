// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Tiles/TileDataAsset.h"
#include "CollapseHandlerComponent.generated.h"

UENUM(BlueprintType)
enum class ECollapseMethod : uint8 {
	C_SmallestFirst		UMETA(DisplayName = "Smallest First"),
	C_SmallestFirstC	UMETA(DisplayName = "Smallest First, from center of map"),
	C_HorizontalScanLR	UMETA(DisplayName = "Horizontal Scan: Left->Right"),
	C_HorizontalScanRL	UMETA(DisplayName = "Horizontal Scan: Right->Left"),
	C_VerticalScanTB	UMETA(DisplayName = "Vertical Scan: Top->Bottom"),
	C_VerticalScanBT	UMETA(DisplayName = "Vertical Scan: Bottom->Top"),
};

class UPaperTileMapComponent;
class UTileDataAsset;
class UTileObject;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AGORA_API UCollapseHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	bool IsSetup;

	UPROPERTY()
	bool IsCollapseStarted;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UTileDataAsset>> AvailableTiles;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FPaperTileInfo NumberTilesInfo;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UPaperTileMapComponent* TileMapRef;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<UTileObject*> MapTiles;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	int32 MapWidth;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	int32 MapHeight;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	int32 MapDepth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	ECollapseMethod CollapseMethod;
	
	UPROPERTY()
	UTileObject* LastCollapsedTile;
	
public:	
	// Sets default values for this component's properties
	UCollapseHandlerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Setup(UPaperTileMapComponent* TileMap);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void NextFrame();
	virtual void NextFrame_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TArray<UTileObject*> GetNeighbors(int32 x, int32 y) const;
	virtual TArray<UTileObject*> GetNeighbors_Implementation(int32 x, int32 y) const;

	UFUNCTION(BlueprintCallable)
	void SetTileFromGraphicArray(int32 TileIndex, TMap<EMapLayer, FPaperTileInfo>& Graphics);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnTileCollapsed(int32 X, int32 Y);
	virtual void OnTileCollapsed_Implementation(int32 X, int32 Y);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnTileDataChanged(int32 X, int32 Y);
	virtual void OnTileDataChanged_Implementation(int32 X, int32 Y);
};

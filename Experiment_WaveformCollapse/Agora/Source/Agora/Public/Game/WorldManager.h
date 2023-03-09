// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperTileLayer.h"

#include "WorldManager.generated.h"

UCLASS(BlueprintType, Blueprintable, Abstract, ClassGroup = (Custom))
class AGORA_API AWorldManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWorldManager();

#if WITH_EDITORONLY_DATA
private:
	UPROPERTY()
	class UBillboardComponent* BillboardComponent;

	UPROPERTY()
	class UArrowComponent* ArrowComponent;

public:
	UPROPERTY(EditAnywhere)
	bool RefreshTileMap;
#endif
	
private:
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WorldManager", meta = (AllowPrivateAccess = "true")) //ExposeFunctionCategories = "Sprite,Rendering,Physics,Components|Sprite", 
	//class UPaperTileMapComponent* TileMapComponent;

	/** Returns RenderComponent subobject **/
	//FORCEINLINE class UPaperTileMapComponent* GetRenderComponent() const { return TileMapComponent; }

	UPROPERTY(VisibleAnywhere, Category = "WorldManager|Refs")
	class UPaperTileMapComponent* TileMapComponentRef;

	UPROPERTY(VisibleAnywhere, Category = "WorldManager|Refs")
	class UPaperTileMap* TileMapRef;

	UPROPERTY(BlueprintReadOnly, Category = "WorldManager|Refs", meta = (AllowPrivateAccess = "true"))
	FVector2D TileSizeInUnits;

	UPROPERTY()
	FBox WorldBoundingBox;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WorldManager|Refs")
	class APaperTileMapActor* TileMapActorRef;

	UFUNCTION(BlueprintCallable, Category = "WorldManager")
	FORCEINLINE FBox GetWorldBounds() const { return WorldBoundingBox; }

	/** Gets if the location is within the world bounding box on the X axis.
	* @param	Location	The world location to check
	* @return				0 if within bounds, -1 if below the minimum, 1 if above the maximum
	*/
	UFUNCTION(BlueprintCallable, Category = "WorldManager")
	int32 IsInBoundsX(FVector Location) const;


	/** Gets if the location is within the world bounding box on the Y axis.
	* @param	Location	The world location to check
	* @return				0 if within bounds, -1 if below the minimum, 1 if above the maximum
	*/
	UFUNCTION(BlueprintCallable, Category = "WorldManager")
	int32 IsInBoundsY(FVector Location) const;

	UFUNCTION(BlueprintCallable, Category = "WorldManager")
	FVector2D GetGridSize() const;

	UFUNCTION(BlueprintCallable, Category = "WorldManager|Utility")
	FVector ClampToBounds(FVector Location);

	UFUNCTION(BlueprintCallable, Category = "WorldManager")
	void RecalculateWorld();

	UFUNCTION(BlueprintCallable, Category = "WorldManager")
	void ToggleGrid();

	UFUNCTION(BlueprintCallable, Category = "WorldManager|Utility")
	FVector SnapLocationToGrid(const FVector Location, bool SnapToTileCenter = true) const;

	UFUNCTION(BlueprintCallable, Category = "WorldManager|Utility")
	void ConvertLocationToTileIndex(const FVector Location, FVector2D& TileIndex) const;

	UFUNCTION(BlueprintCallable, Category = "WorldManager|Utility")
	void ConvertTileIndexToLocation(const int32 Index, FVector& Location) const;

	UFUNCTION(BlueprintCallable, Category = "WorldManager")
	void SetTile(const FVector2D TileIndex, const FPaperTileInfo TileInfo, int32 LayerIndex);

	UFUNCTION(BlueprintCallable, Category = "WorldManager")
	void SetTileFromWorld(const FVector Location, const FPaperTileInfo TileInfo, int32 LayerIndex);

	UFUNCTION(BlueprintCallable, Category = "WorldManager")
	bool GetLayerIndex(FString LayerName, int32& LayerIndex) const;
};

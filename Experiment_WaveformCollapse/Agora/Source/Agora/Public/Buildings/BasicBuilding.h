// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicBuilding.generated.h"

UCLASS(BlueprintType, Blueprintable, Abstract)
class AGORA_API ABasicBuilding : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionBox;

public:	
	// Sets default values for this actor's properties
	ABasicBuilding();

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class AWorldManager* WorldManagerRef;

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Building")
	class UPaperTileMap* TileMapRef;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Building")
	FString LayerName;
};

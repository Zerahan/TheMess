// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building_Ghost.generated.h"

class ABuilding_Basic;

UCLASS(Blueprintable, BlueprintType, Abstract)
class EXPERIMENT_AITEST_API ABuilding_Ghost : public AActor
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABuilding_Basic> BuildingClassRef;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMeshComponent*> StaticMeshes;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UMaterial> GhostMaterial;
	
public:	
	// Sets default values for this actor's properties
	ABuilding_Ghost();
	ABuilding_Ghost(TSubclassOf<ABuilding_Basic> BuildingClass);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPlaceGhost();
	virtual void OnPlaceGhost_Implementation();
};

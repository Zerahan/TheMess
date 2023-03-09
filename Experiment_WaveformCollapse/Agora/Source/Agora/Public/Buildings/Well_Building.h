// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buildings/BasicBuilding.h"
#include "Well_Building.generated.h"

/**
 * 
 */
UCLASS()
class AGORA_API AWell_Building : public ABasicBuilding
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABasicBuilding> BuildingClassToAttract;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	int32 MaxNumberOfBuildingsToAttract;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float EffectiveRadius;

public:
	AWell_Building();

protected:
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
};

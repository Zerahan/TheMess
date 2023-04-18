// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Data/FactionTypes.h"
#include "AITestPlayerController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class EXPERIMENT_AITEST_API AAITestPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	EFaction MyFaction;

public:
	AAITestPlayerController();

protected:
	virtual void BeginPlay() override;
};

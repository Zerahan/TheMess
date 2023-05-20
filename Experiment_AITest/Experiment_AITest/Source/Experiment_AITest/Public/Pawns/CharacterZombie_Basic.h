// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/GASCharacter_Basic.h"
#include "CharacterZombie_Basic.generated.h"

class UAIPerceptionComponent;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class EXPERIMENT_AITEST_API ACharacterZombie_Basic : public AGASCharacter_Basic
{
	GENERATED_BODY()
	
	UAIPerceptionComponent* PerceptionComponent;

public:
	ACharacterZombie_Basic();

};

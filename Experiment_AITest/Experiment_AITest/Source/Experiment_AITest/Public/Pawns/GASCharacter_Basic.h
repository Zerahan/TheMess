// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GASCharacter_Basic.generated.h"

UCLASS(BlueprintType, Blueprintable, Abstract)
class EXPERIMENT_AITEST_API AGASCharacter_Basic : public ACharacter
{
	GENERATED_BODY()

	class UAbilitySystemComponent_Basic* GASComponent;

public:
	// Sets default values for this character's properties
	AGASCharacter_Basic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemComponent_Basic.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReceivedDamageDelegate, UAbilitySystemComponent_Basic*, SourceComponent, float, RawDamage, float, ModifiedDamage);

/**
 * 
 */
UCLASS()
class EXPERIMENT_AITEST_API UAbilitySystemComponent_Basic : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	bool CharacterAbilitiesGiven = false;
	bool StartupEffectsApplies = false;

	UPROPERTY(BlueprintAssignable)
	FReceivedDamageDelegate ReceivedDamage;

	virtual void RecieveDamage(UAbilitySystemComponent_Basic* SourceComponent, float RawDamage, float ModifiedDamage);
};

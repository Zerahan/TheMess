// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AbilitySystemComponent_Basic.h"

void UAbilitySystemComponent_Basic::RecieveDamage(UAbilitySystemComponent_Basic* SourceComponent, float RawDamage, float ModifiedDamage)
{
	ReceivedDamage.Broadcast(SourceComponent, RawDamage, ModifiedDamage);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSet_Basic.h"
#include "Net/UnrealNetwork.h"

void UAttributeSet_Basic::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSet_Basic, Health, OldValue);
}

void UAttributeSet_Basic::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSet_Basic, MaxHealth, OldValue);
}

void UAttributeSet_Basic::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSet_Basic, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSet_Basic, MaxHealth, COND_None, REPNOTIFY_Always);
}

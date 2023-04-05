// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UnitStatusComponent.h"

// Sets default values for this component's properties
UUnitStatusComponent::UUnitStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	HitPoints_Max		= 100.f;
	HitPoints			= HitPoints_Max;
	IsAlive				= true;
	IsInvulnerable		= false;
	CanBeRevivedOnHeal	= true;

	// ...
}


// Called when the game starts
void UUnitStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
void UUnitStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

float UUnitStatusComponent::GetHitPoints() const { return HitPoints; }

float UUnitStatusComponent::SetHitPoints(float Value, bool ApplyAsModifier) {
	if (Value == 0 && ApplyAsModifier) return HitPoints;
	if (Value == HitPoints && !ApplyAsModifier) return HitPoints;

	if (ApplyAsModifier) {
		if (IsInvulnerable && Value < 0) return HitPoints;
		HitPoints = FMath::Clamp(HitPoints + Value, 0.f, GetMaxHitPoints());
	}
	else {
		HitPoints = Value;
	}
	OnHitPointsChanged();
	
	return HitPoints;
}

float UUnitStatusComponent::GetMaxHitPoints() const { return HitPoints_Max; }

float UUnitStatusComponent::SetMaxHitPoints(float Value, bool ApplyAsModifier) {
	HitPoints_Max = ((ApplyAsModifier) ? (HitPoints_Max + Value) : Value);
	if (HitPoints > HitPoints_Max) HitPoints = HitPoints_Max;
	return HitPoints_Max;
}

bool UUnitStatusComponent::GetIsAlive() const { return IsAlive; }

bool UUnitStatusComponent::SetIsAlive(bool Value) { IsAlive = Value; return IsAlive; }

float UUnitStatusComponent::TakeDamage_Implementation(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	
	if (IsInvulnerable || !GetOwner()->CanBeDamaged()) return DamageAmount;
	float ActualDamage = DamageAmount;
	if (ActualDamage > HitPoints) {
		ActualDamage = HitPoints;
		SetHitPoints(0, false);
		DoKill();
	}
	else {
		SetHitPoints(0 - ActualDamage, true);
		if (ActualDamage < 0 && CanBeRevivedOnHeal) {
			DoRevive();
		}
	}
	return ActualDamage;
}

void UUnitStatusComponent::OnHitPointsChanged_Implementation()
{
	OnHealthChanged.Broadcast(HitPoints);
}

void UUnitStatusComponent::DoKill_Implementation()
{
	if (IsAlive){
		IsAlive = false;
		OnKilled.Broadcast();
	}
}

void UUnitStatusComponent::DoRevive_Implementation()
{
	if (!IsAlive) {
		IsAlive = true;
		OnRevived.Broadcast();
	}
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/Building_Basic.h"

// Sets default values
ABuilding_Basic::ABuilding_Basic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitPoints_Max	= 100.f;
	HitPoints		= HitPoints_Max;
	IsAlive			= true;
	IsInvulnerable	= false;
}

// Called when the game starts or when spawned
void ABuilding_Basic::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuilding_Basic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABuilding_Basic::GetHitPoints() const { return HitPoints; }

float ABuilding_Basic::SetHitPoints(float Value, bool ApplyAsModifier) {
	if (ApplyAsModifier) {
		if (IsInvulnerable) return HitPoints;
		HitPoints = FMath::Clamp(HitPoints + Value, 0.f, GetMaxHitPoints());
	}
	else {
		HitPoints = Value;
	}
	return HitPoints;
}

float ABuilding_Basic::GetMaxHitPoints() const { return HitPoints_Max; }

float ABuilding_Basic::SetMaxHitPoints(float Value, bool ApplyAsModifier) {
	HitPoints_Max = ((ApplyAsModifier) ? (HitPoints_Max + Value) : Value);
	if(HitPoints > HitPoints_Max) HitPoints = HitPoints_Max;
	return HitPoints_Max;
}

bool ABuilding_Basic::GetIsAlive() const { return IsAlive; }

bool ABuilding_Basic::SetIsAlive(bool Value) { IsAlive = Value; return IsAlive; }

float ABuilding_Basic::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if(IsInvulnerable || !CanBeDamaged()) return DamageAmount;
	float ActualDamage = DamageAmount;
	if (ActualDamage > HitPoints) {
		ActualDamage = HitPoints;
		HitPoints = 0;
		OnKilled();
	}
	else {
		HitPoints = FMath::Clamp(HitPoints - ActualDamage, 0.f, HitPoints_Max);
	}
	return Super::TakeDamage(ActualDamage, DamageEvent, EventInstigator, DamageCauser);
}

void ABuilding_Basic::OnKilled_Implementation()
{
	if (IsAlive) IsAlive = false;
}


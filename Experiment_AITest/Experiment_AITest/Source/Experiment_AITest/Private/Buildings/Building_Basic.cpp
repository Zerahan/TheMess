// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/Building_Basic.h"
#include "Components/UnitStatusComponent.h"

// Sets default values
ABuilding_Basic::ABuilding_Basic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StatusComponent = CreateDefaultSubobject<UUnitStatusComponent>(TEXT("Status Component"));
}

// Called when the game starts or when spawned
void ABuilding_Basic::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(GetStatusComponent())) {
		GetStatusComponent()->OnHealthChanged.AddDynamic(this, &ABuilding_Basic::OnHitPointsChanged);
	}
}

// Called every frame
void ABuilding_Basic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
UUnitStatusComponent* ABuilding_Basic::GetStatusComponent() const { return StatusComponent; }

float ABuilding_Basic::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (IsValid(GetStatusComponent())) {
		return Super::TakeDamage(GetStatusComponent()->TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser), DamageEvent, EventInstigator, DamageCauser);
	}
	else {
		return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	}
}


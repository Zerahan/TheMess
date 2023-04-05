// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/AICharacter_Basic.h"
#include "Components/UnitStatusComponent.h"

// Sets default values
AAICharacter_Basic::AAICharacter_Basic()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StatusComponent = CreateDefaultSubobject<UUnitStatusComponent>(TEXT("Status Component"));
}

// Called when the game starts or when spawned
void AAICharacter_Basic::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAICharacter_Basic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UUnitStatusComponent* AAICharacter_Basic::GetStatusComponent() const { return StatusComponent; }

float AAICharacter_Basic::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (IsValid(GetStatusComponent())) {
		return Super::TakeDamage(GetStatusComponent()->TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser), DamageEvent, EventInstigator, DamageCauser);
	}
	else {
		return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	}
}


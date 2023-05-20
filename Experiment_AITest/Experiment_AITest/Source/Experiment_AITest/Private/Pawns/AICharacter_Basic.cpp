// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/AICharacter_Basic.h"
#include "Components/CapsuleComponent.h"
#include "Components/UnitStatusComponent.h"
#include "GAS/AbilitySystemComponent_Basic.h"

AAICharacter_Basic::AAICharacter_Basic(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StatusComponent = CreateDefaultSubobject<UUnitStatusComponent>(TEXT("Status Component"));

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);

	bAlwaysRelevant = true;
	SubunitCount	= 1;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	EffectRemoveOnDeathTag = FGameplayTag::RequestGameplayTag(FName("State.RemoveOnDeath"));

}

uint8 AAICharacter_Basic::GetSubunitCount() const
{
	return SubunitCount;
}

void AAICharacter_Basic::SetSubunitCount(uint8 NewCount, bool OverwriteCount)
{
	SubunitCount = (OverwriteCount ? 0 : SubunitCount) + NewCount;
}

bool AAICharacter_Basic::TryMergeUnit(AAICharacter_Basic* OtherUnit)
{
	if(!IsValid(OtherUnit)) return true;
	bool HasMerged = false;
	if (OtherUnit->GetSubunitCount() > 0) {
		SubunitCount += OtherUnit->GetSubunitCount();
		//Destroy(OtherUnit);
		HasMerged = true;
	}
	return HasMerged;
}

float AAICharacter_Basic::GetHealth() const
{
	return 0.0f;
}

float AAICharacter_Basic::GetMaxHealth() const
{
	return 0.0f;
}

// Called when the game starts or when spawned
void AAICharacter_Basic::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAICharacter_Basic::AddCharacterAbilities()
{
}

void AAICharacter_Basic::InitializeAttributes()
{
}

void AAICharacter_Basic::AddStartupEffects()
{
}

void AAICharacter_Basic::SetHealth(float NewValue)
{
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

UAbilitySystemComponent* AAICharacter_Basic::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

bool AAICharacter_Basic::IsAlive() const
{
	return GetHealth() > 0;
}

int32 AAICharacter_Basic::GetAbilityLevel(AITestAbilityID ID) const
{
	return 1;
}

void AAICharacter_Basic::RemoveAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || !AbilitySystemComponent->CharacterAbilitiesGiven) {
		return;
	}

	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities()) {
		if ((Spec.SourceObject == this) && CharacterAbilities.Contains(Spec.Ability->GetClass())) {
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}

	for (int32 i = 0; i < AbilitiesToRemove.Num(); i++) {
		AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
	}

	AbilitySystemComponent->CharacterAbilitiesGiven = false;
}

void AAICharacter_Basic::StartDeath()
{
}

void AAICharacter_Basic::FinishDeath()
{
}

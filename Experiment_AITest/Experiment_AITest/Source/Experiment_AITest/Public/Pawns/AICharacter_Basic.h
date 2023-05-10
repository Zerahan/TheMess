// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GAS/AbilitySystemComponent_Basic.h"
#include <Experiment_AITest/Experiment_AITest.h>
#include "AICharacter_Basic.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterDiedDelegate, AAICharacter_Basic*, Character);

class UUnitStatusComponent;

UCLASS(BlueprintType, Blueprintable, Abstract)
class EXPERIMENT_AITEST_API AAICharacter_Basic : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UUnitStatusComponent* StatusComponent;

public:
	// Sets default values for this character's properties
	AAICharacter_Basic(const class FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable)
	FOnCharacterDiedDelegate OnCharacterDied;

	UFUNCTION(BlueprintCallable)
	virtual bool IsAlive() const;

	UFUNCTION(BlueprintCallable)
	virtual int32 GetAbilityLevel(AITestAbilityID ID) const;

	virtual void RemoveAbilities();

	UFUNCTION(BlueprintCallable)
	virtual void StartDeath();

	UFUNCTION(BlueprintCallable)
	virtual void FinishDeath();

	UFUNCTION(BlueprintCallable)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TWeakObjectPtr<class UAbilitySystemComponent_Basic> AbilitySystemComponent;
	TWeakObjectPtr<class UAttributeSet_Basic> AttributeSet;

	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText CharacterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* DeathMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<TSubclassOf<class UGameplayAbility>> CharacterAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	virtual void AddCharacterAbilities();

	virtual void InitializeAttributes();

	virtual void AddStartupEffects();

	virtual void SetHealth(float NewValue);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	UUnitStatusComponent* GetStatusComponent() const;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateGraphics();
	virtual void UpdateGraphics_Implementation() {}

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnitStatusComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, const float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKilled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRevived);


UCLASS( BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXPERIMENT_AITEST_API UUnitStatusComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, meta = (AllowPrivateAccess = "true"))
	float HitPoints;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float HitPoints_Max;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, meta = (AllowPrivateAccess = "true"))
	bool IsAlive;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	bool IsInvulnerable;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	bool CanBeRevivedOnHeal;

public:	
	// Sets default values for this component's properties
	UUnitStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float GetHitPoints() const;

	UFUNCTION(BlueprintCallable)
	float SetHitPoints(float Value, bool ApplyAsModifier = true);

	UFUNCTION(BlueprintCallable)
	float GetMaxHitPoints() const;

	UFUNCTION(BlueprintCallable)
	float SetMaxHitPoints(float Value, bool ApplyAsModifier = true);

	UFUNCTION(BlueprintCallable)
	bool GetIsAlive() const;
	
	UFUNCTION(BlueprintCallable)
	bool SetIsAlive(bool Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
	virtual float TakeDamage_Implementation(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnHitPointsChanged();
	virtual void OnHitPointsChanged_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DoKill();
	virtual void DoKill_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DoRevive();
	virtual void DoRevive_Implementation();

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnKilled OnKilled;

	UPROPERTY(BlueprintAssignable)
	FOnRevived OnRevived;
	
};

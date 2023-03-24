// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building_Basic.generated.h"

UCLASS(Blueprintable, BlueprintType, Abstract)
class EXPERIMENT_AITEST_API ABuilding_Basic : public AActor
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, meta = (AllowPrivateAccess = "true"))
	float HitPoints;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(AllowPrivateAccess="true"))
	float HitPoints_Max;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, meta = (AllowPrivateAccess = "true"))
	bool IsAlive;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	bool IsInvulnerable;
	
public:	
	// Sets default values for this actor's properties
	ABuilding_Basic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnKilled();
	virtual void OnKilled_Implementation();
};

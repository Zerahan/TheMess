// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building_Basic.generated.h"

class UUnitStatusComponent;

UCLASS(Blueprintable, BlueprintType, Abstract)
class EXPERIMENT_AITEST_API ABuilding_Basic : public AActor
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UUnitStatusComponent* StatusComponent;
	
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
	UUnitStatusComponent* GetStatusComponent() const;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateGraphics();
	virtual void UpdateGraphics_Implementation(){}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnHitPointsChanged(const float HitPoints);
	virtual void OnHitPointsChanged_Implementation(const float HitPoints){}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void BuildGhost(TArray<UStaticMesh*>& Meshes, TArray<FTransform>& Transforms) const;
	virtual void BuildGhost_Implementation(TArray<UStaticMesh*>& Meshes, TArray<FTransform>& Transforms) const;
};

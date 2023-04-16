// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buildings/Building_Basic.h"
#include "Buildings/WorkerAITypes.h"
#include "Interfaces/WorkableInterface.h"
#include "WorkableBuilding_Basic.generated.h"

class UItemData;
class UBuildingDataAsset;
class AWorkerCharacter_Basic;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class EXPERIMENT_AITEST_API AWorkableBuilding_Basic : public ABuilding_Basic , public IWorkableInterface
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	UBuildingDataAsset* StaticData;
	
	UPROPERTY()
	TMap<EWorkType, bool> IsWorkTypeAvailable;

	UPROPERTY()
	TArray<AWorkerCharacter_Basic*> AssignedWorkers;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	int32 MaxAssignedWorkers;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, meta = (AllowPrivateAccess = "true"))
	uint8 StateID;

protected:
	virtual void BeginPlay() override;
	
public:
	AWorkableBuilding_Basic();

	virtual bool CanDoWork_Implementation(AActor* Worker, const EWorkType WorkType) const;
	virtual bool DoWork_Implementation(AActor* Worker, const EWorkType WorkType);

	virtual void OnHitPointsChanged_Implementation(const float HitPoints) override;
	
	virtual float GetWorkTime_Implementation(const EWorkType WorkType) const override;

	virtual bool GetWorkLocation_Implementation(const EWorkType WorkType, AActor*& WorkTarget, FVector& WorkLocation) const override;
	
	UFUNCTION(BlueprintCallable)
	UBuildingDataAsset* GetStaticData() const;

	UFUNCTION(BlueprintCallable)
	uint8 GetStateID() const;

	UFUNCTION(BlueprintCallable)
	uint8 SetStateID(uint8 NewStateID);

	/*
	*	Sets the availability of one of the work types
	*	@param WorkType			The WorkType enum to change
	*	@param NewAvailability	The new availability of the work type
	*/
	UFUNCTION(BlueprintCallable)
	void UpdateWorkTypeAvailability(EWorkType WorkType, bool NewAvailability);

	/*
	*	Try to assign a worker to this building.
	*	@param NewWorker	The worker to assign
	*	@return				Returns if the worker was able to be assigned to this building.
	*/
	UFUNCTION(BlueprintCallable)
	bool AssignNewWorker(AWorkerCharacter_Basic* NewWorker, bool IgnoreOneUnitLimit = false);

	UFUNCTION(BlueprintCallable)
	bool UnassignWorker(AWorkerCharacter_Basic* Worker);
};

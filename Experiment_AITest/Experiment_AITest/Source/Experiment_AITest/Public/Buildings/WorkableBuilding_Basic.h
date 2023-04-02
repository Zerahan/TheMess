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
	TSubclassOf<UBuildingDataAsset> StaticData;
	
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

	virtual bool CanDoWork_Implementation(const AActor* Worker, const EWorkType WorkType, const UItemData* AvailableItem = nullptr) const;
	virtual bool DoWork_Implementation(const AActor* Worker, const EWorkType WorkType, const UItemData* AvailableItem = nullptr);
	virtual int32 GetRequiredItem_Implementation(const AActor* Worker, const EWorkType WorkType, TSubclassOf<UItemData>& ItemType) const;
	
	UFUNCTION(BlueprintCallable)
	UBuildingDataAsset* GetStaticData() const;

	UFUNCTION(BlueprintCallable)
	uint8 GetStateID() const;

	UFUNCTION(BlueprintCallable)
	uint8 SetStateID(uint8 NewStateID);
	
	/*
	*	Is this work type valid for this building, and is it currently available.
	*	@param WorkType	The worktype enum we are checking.
	*	@return			If this type of work can be performed on this building.
	*/
	UFUNCTION(BlueprintCallable)
	bool CanWorkBuilding(EWorkType WorkType) const;

	/*
	*	Attempt to apply work to a building, and retrieve the item results of that work
	*	@param WorkingActor			The actor performing the work
	*	@param WorkType				The type of work the actor is attempting to perform
	*	@param ReturnedProduction	The items generated from performing the work (if anything)
	*	@return						If the work could be done at this time.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool WorkBuilding(AActor* WorkingActor, EWorkType WorkType, TArray<UItemData*>& ReturnedProduction);
	virtual bool WorkBuilding_Implementation(AActor* WorkingActor, EWorkType WorkType, TArray<UItemData*>& ReturnedProduction);

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
	bool AssignNewWorker(AWorkerCharacter_Basic* NewWorker);

	UFUNCTION(BlueprintCallable)
	bool UnassignWorker(AWorkerCharacter_Basic* Worker);
};

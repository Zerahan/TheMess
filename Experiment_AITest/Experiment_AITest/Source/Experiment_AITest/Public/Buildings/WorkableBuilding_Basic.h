// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buildings/Building_Basic.h"
#include "Buildings/WorkerAITypes.h"
#include "Interfaces/WorkableInterface.h"
#include "WorkableBuilding_Basic.generated.h"

class UItemData;
class UBuildingDataAsset;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class EXPERIMENT_AITEST_API AWorkableBuilding_Basic : public ABuilding_Basic , public IWorkableInterface
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	UBuildingDataAsset* StaticData;

	TMap<EWorkType, bool> IsWorkTypeAvailable;

protected:
	virtual void BeginPlay();
	
public:
	virtual bool CanDoWork_Implementation(const AActor* Worker, const EWorkType WorkType, const UItemData* AvailableItem = nullptr) const;
	virtual bool DoWork_Implementation(const AActor* Worker, const EWorkType WorkType, const UItemData* AvailableItem = nullptr);
	virtual int32 GetRequiredItem_Implementation(const EWorkType WorkType, TSubclassOf<UItemData>& ItemType) const;
	
	UFUNCTION(BlueprintCallable)
	UBuildingDataAsset* GetStaticData() const;
	
	UFUNCTION(BlueprintCallable)
	bool CanWorkBuilding(EWorkType WorkType) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool WorkBuilding(AActor* WorkingActor, EWorkType WorkType, TArray<UItemData*>& ReturnedProduction);
	virtual bool WorkBuilding_Implementation(AActor* WorkingActor, EWorkType WorkType, TArray<UItemData*>& ReturnedProduction);

	UFUNCTION(BlueprintCallable)
	void UpdateWorkTypeAvailability(EWorkType WorkType, bool NewAvailability);
};

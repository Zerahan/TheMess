// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buildings/Building_Basic.h"
#include "Buildings/WorkerAITypes.h"
#include "Interfaces/WorkableInterface.h"
#include "WorkableBuilding_Basic.generated.h"

class UItemData;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class EXPERIMENT_AITEST_API AWorkableBuilding_Basic : public ABuilding_Basic , public IWorkableInterface
{
	GENERATED_BODY()
	
public:
	virtual bool CanDoWork_Implementation(const AActor* Worker, const EWorkType WorkType, const UItemData* AvailableItem = nullptr) const;
	virtual bool DoWork_Implementation(const AActor* Worker, const EWorkType WorkType, const UItemData* AvailableItem = nullptr);
	virtual int32 GetRequiredItem_Implementation(const EWorkType WorkType, TSubclassOf<UItemData>& ItemType) const;
};

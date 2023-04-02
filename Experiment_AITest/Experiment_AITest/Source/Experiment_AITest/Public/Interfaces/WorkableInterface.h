// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WorkableInterface.generated.h"

class UItemData;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWorkableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class EXPERIMENT_AITEST_API IWorkableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/*
	* What is the item type and amount required for this type of work to be done?
	* @param WorkType	The type of work being done
	* @param ItemType	The class of item that type of work requires
	* @return			How much of ItemType is required to do this work?
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int32 GetRequiredItem(const AActor* Worker, const EWorkType WorkType, TSubclassOf<UItemData>& ItemType) const;

	/*
	* Can this worker do this type of work for the building?
	* @param Worker		The actor doing the work
	* @param WorkType	The type of work being done
	* @return			Can this type of work be done?
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CanDoWork(const AActor* Worker, const EWorkType WorkType, const UItemData* AvailableItem = nullptr) const;
	
	/*
	* Performs a type of work for the building. Ex: Till land, reload turret, etc
	* @param Worker		The actor doing the work
	* @param WorkType	The type of work being done
	* @return			Did the work successfully execute?
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool DoWork(const AActor* Worker, const EWorkType WorkType, const UItemData* AvailableItem = nullptr);
};

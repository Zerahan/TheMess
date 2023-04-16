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
	* Can this worker do this type of work for the building?
	* @param Worker		The actor doing the work
	* @param WorkType	The type of work being done
	* @return			Can this type of work be done?
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CanDoWork(AActor* Worker, const EWorkType WorkType) const;
	
	/*
	* Performs a type of work for the building. Ex: Till land, reload turret, etc
	* @param Worker		The actor doing the work
	* @param WorkType	The type of work being done
	* @return			Did the work successfully execute?
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool DoWork(AActor* Worker, const EWorkType WorkType);

	/*
	* How much time in seconds does it take to perform this work?
	* @param WorkType	The type of work being done
	* @return			The amount of time in seconds to perform this work.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetWorkTime(const EWorkType WorkType) const;

	/*
	* Get the target actor and/or target location the pawn needs to move to to perform this work.
	* @param WorkType		The type of work being done
	* @param WorkTarget		The actor that should be targeted for this work
	* @param WorkLocation	The location that should be targeted for this work
	* @return				Was this request successfull?
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool GetWorkLocation(const EWorkType WorkType, AActor*& WorkTarget, FVector& WorkLocation) const;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WorkerAITypes.generated.h"

UENUM(BlueprintType)
enum class EWorkType : uint8
{
	W_Undefined		UMETA(DisplayName = "Undefined"),
	W_Generic		UMETA(DisplayName = "Generic"),
	W_Repair		UMETA(DisplayName = "Repair"),
	W_Target		UMETA(DisplayName = "Targeting"),
	W_Reload		UMETA(DisplayName = "Reload"),
	W_Attack		UMETA(DisplayName = "Attack"),
	W_Deposit		UMETA(DisplayName = "Deposit"),
	W_Withdraw		UMETA(DisplayName = "Withdraw"),
};
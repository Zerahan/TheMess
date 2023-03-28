// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Globals.generated.h"

UENUM(BlueprintType)
enum class EError : uint8 {
	FAIL			= 0 UMETA(DisplayName = "Failed"),
	SUCCESS			= 1 UMETA(DisplayName = "Success"),
	INVALID			= 2 UMETA(DisplayName = "Invalid Data"),
	NOTWHITELISTED	= 3 UMETA(DisplayName = "Not On Whitelist"),
	NOTBLACKLISTED	= 4 UMETA(DisplayName = "Not On Blacklist"),
};
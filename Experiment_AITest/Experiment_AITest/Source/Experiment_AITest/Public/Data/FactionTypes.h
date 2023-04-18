// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FactionTypes.generated.h"
/*
#include "Data/FactionTypes.h"
//*/

UENUM(BlueprintType)
enum class EFaction : uint8 {
	Unassigned	UMETA(DisplayName = "Unassigned"),
	Faction1	UMETA(DisplayName = "Faction 1"),
	Faction2	UMETA(DisplayName = "Faction 2"),
	Faction3	UMETA(DisplayName = "Faction 3"),
	Faction4	UMETA(DisplayName = "Faction 4"),
	Faction5	UMETA(DisplayName = "Faction 5"),
	Faction6	UMETA(DisplayName = "Faction 6"),
	Faction7	UMETA(DisplayName = "Faction 7"),
	Faction8	UMETA(DisplayName = "Faction 8"),
	Count		UMETA(Hidden),
};
ENUM_RANGE_BY_COUNT(EFaction, EFaction::Count);
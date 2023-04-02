// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/BuildingFunctionLibrary.h"

int32 UBuildingFunctionLibrary::FindClosestActorInArray(TArray<AActor*> Actors, AActor* OriginActor) {
	if (Actors.Num() == 0) return -1;
	int32 ClosestIndex = 0;
	float ClosestDistance = OriginActor->GetDistanceTo(Actors[0]);
	for (int32 i = 0; i < Actors.Num(); i++) {
		if (OriginActor->GetDistanceTo(Actors[i]) < ClosestDistance) {
			ClosestIndex = i;
			ClosestDistance = OriginActor->GetDistanceTo(Actors[i]);
		}
	}
	return ClosestIndex;
}

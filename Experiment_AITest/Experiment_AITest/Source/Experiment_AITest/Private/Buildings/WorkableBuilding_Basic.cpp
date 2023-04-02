// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/WorkableBuilding_Basic.h"
#include "Data/BuildingDataAsset.h"
#include "Inventory/ItemData.h"
#include "Pawns/WorkerCharacter_Basic.h"

void AWorkableBuilding_Basic::BeginPlay()
{
    if (IsValid(GetStaticData())) {
        TMap<EWorkType, FWorkData> Info = GetStaticData()->GetWorkInfo();
        TArray<EWorkType> Keys;
        Info.GetKeys(Keys);
        for (auto K : Keys) {
            IsWorkTypeAvailable.Add(K, false);
        }
        AssignedWorkers.Empty();
        AssignedWorkers.SetNum(MaxAssignedWorkers);
        for (int i = 0; i < MaxAssignedWorkers; i++) {
            AssignedWorkers[i] = nullptr;
        }
        FString Name = GetStaticData()->GetDisplayName().ToString();
        Name.RemoveSpacesInline();
        //Name.ToLowerInline();
        Tags.Add(FName(Name));
    }
    Super::BeginPlay();
}

AWorkableBuilding_Basic::AWorkableBuilding_Basic()
    : Super()
{
    MaxAssignedWorkers = 1;
}

bool AWorkableBuilding_Basic::CanDoWork_Implementation(const AActor* Worker, const EWorkType WorkType, const UItemData* AvailableItem) const
{
    return CanWorkBuilding(WorkType);
}

bool AWorkableBuilding_Basic::DoWork_Implementation(const AActor* Worker, const EWorkType WorkType, const UItemData* AvailableItem)
{
    return false;//WorkBuilding(Worker, WorkType, TArray<UItemData*>());
}

int32 AWorkableBuilding_Basic::GetRequiredItem_Implementation(const AActor* Worker, const EWorkType WorkType, TSubclassOf<UItemData>& ItemType) const
{
    return 0;
}

UBuildingDataAsset* AWorkableBuilding_Basic::GetStaticData() const { return StaticData.GetDefaultObject(); }

uint8 AWorkableBuilding_Basic::GetStateID() const { return StateID; }

uint8 AWorkableBuilding_Basic::SetStateID(uint8 NewStateID) {
    StateID = NewStateID;
    return StateID;
}

bool AWorkableBuilding_Basic::CanWorkBuilding(EWorkType WorkType) const {
    if (!IsValid(GetStaticData())) return false;
    if (!GetStaticData()->IsValidWorkType(WorkType)) return false;
    return *IsWorkTypeAvailable.Find(WorkType);
}

bool AWorkableBuilding_Basic::WorkBuilding_Implementation(AActor* WorkingActor, EWorkType WorkType, TArray<UItemData*>& ReturnedProduction)
{
    if(!CanWorkBuilding(WorkType)) return false;
    ReturnedProduction = GetStaticData()->DoProduction(WorkingActor, WorkType);
    //GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Production: %i"), ReturnedProduction.Num()));
    return true;
}

void AWorkableBuilding_Basic::UpdateWorkTypeAvailability(EWorkType WorkType, bool NewAvailability) {
    if(!IsWorkTypeAvailable.Contains(WorkType)) return;
    IsWorkTypeAvailable.Add(WorkType, NewAvailability);
}

bool AWorkableBuilding_Basic::AssignNewWorker(AWorkerCharacter_Basic* NewWorker) {
    if(!IsValid(NewWorker)) return false;
    for (int32 i = 0; i < AssignedWorkers.Num(); i++) {
        if (!IsValid(AssignedWorkers[i])) {
            AssignedWorkers[i] = NewWorker;
            return true;
        }
    }
    return false;
}

bool AWorkableBuilding_Basic::UnassignWorker(AWorkerCharacter_Basic* Worker)
{
    if (!IsValid(Worker)) return false;
    int32 Removed = AssignedWorkers.Remove(Worker);
    return Removed > 0;
}

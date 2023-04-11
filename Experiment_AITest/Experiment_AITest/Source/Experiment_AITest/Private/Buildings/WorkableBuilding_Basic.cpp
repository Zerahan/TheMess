// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/WorkableBuilding_Basic.h"
#include "Data/BuildingDataAsset.h"
#include "Pawns/WorkerCharacter_Basic.h"
#include "Components/UnitStatusComponent.h"

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

bool AWorkableBuilding_Basic::CanDoWork_Implementation(AActor* Worker, const EWorkType WorkType) const
{
    if(!IsWorkTypeAvailable.Contains(WorkType)) return false;
    return *IsWorkTypeAvailable.Find(WorkType);
}

bool AWorkableBuilding_Basic::DoWork_Implementation(AActor* Worker, const EWorkType WorkType)
{
    if (WorkType == EWorkType::W_Repair) {
        if (IsValid(GetStatusComponent())) {
            float RepairAmount = -1 * GetStatusComponent()->GetMaxHitPoints() * 0.1f;
            TakeDamage(RepairAmount, FDamageEvent(), Worker->GetInstigatorController(), Worker);
            return true;
        }
    }
    return false;
}

void AWorkableBuilding_Basic::OnHitPointsChanged_Implementation(const float HitPoints)
{
    if (IsValid(GetStatusComponent())) {
        UpdateWorkTypeAvailability(EWorkType::W_Repair, GetStatusComponent()->GetHitPoints() != GetStatusComponent()->GetMaxHitPoints());
    }
}

float AWorkableBuilding_Basic::GetWorkTime_Implementation(const EWorkType WorkType) const { return 1.f; }

UBuildingDataAsset* AWorkableBuilding_Basic::GetStaticData() const { return StaticData;}//.GetDefaultObject(); }

uint8 AWorkableBuilding_Basic::GetStateID() const { return StateID; }

uint8 AWorkableBuilding_Basic::SetStateID(uint8 NewStateID) {
    StateID = NewStateID;
    return StateID;
}

void AWorkableBuilding_Basic::UpdateWorkTypeAvailability(EWorkType WorkType, bool NewAvailability) {
    if(!IsWorkTypeAvailable.Contains(WorkType)) return;
    IsWorkTypeAvailable.Add(WorkType, NewAvailability);
}

bool AWorkableBuilding_Basic::AssignNewWorker(AWorkerCharacter_Basic* NewWorker, bool IgnoreOneUnitLimit) {
    if(!IsValid(NewWorker)) return false;
    if (!IgnoreOneUnitLimit) {
        for (int32 i = 0; i < AssignedWorkers.Num(); i++) {
            if(IsValid(AssignedWorkers[i])) return false;
        }
    }
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

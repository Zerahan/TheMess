// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/Building_Basic.h"
#include "Components/UnitStatusComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Engine/SCS_Node.h"

// Sets default values
ABuilding_Basic::ABuilding_Basic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default Root Component"));

	StatusComponent = CreateDefaultSubobject<UUnitStatusComponent>(TEXT("Status Component"));
}

// Called when the game starts or when spawned
void ABuilding_Basic::BeginPlay()
{
	if (IsValid(GetStatusComponent())) {
		GetStatusComponent()->OnHealthChanged.AddDynamic(this, &ABuilding_Basic::OnHitPointsChanged);
	}
	Super::BeginPlay();
}

// Called every frame
void ABuilding_Basic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
UUnitStatusComponent* ABuilding_Basic::GetStatusComponent() const { return StatusComponent; }

float ABuilding_Basic::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (IsValid(GetStatusComponent())) {
		return Super::TakeDamage(GetStatusComponent()->TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser), DamageEvent, EventInstigator, DamageCauser);
	}
	else {
		return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	}
}

void ABuilding_Basic::BuildGhost_Implementation(TArray<UStaticMesh*>& Meshes, TArray<FTransform>& Transforms) const {
	TArray<UObject*> SubObjects;
	UBlueprintGeneratedClass* BPClass = Cast<UBlueprintGeneratedClass>(GetClass());
	const TArray<USCS_Node*>& Nodes = BPClass->SimpleConstructionScript->GetAllNodes();

	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Num Meshes: %i"), Nodes.Num()));

	for (USCS_Node* Node : Nodes) {
		if (Node->ComponentClass->IsChildOf<UStaticMeshComponent>()) {
			UStaticMeshComponent* Component = Cast<UStaticMeshComponent>(Node->ComponentTemplate);
			if (Component) {
				if (Component->GetStaticMesh()) {
					Meshes.Add(Component->GetStaticMesh());
					Transforms.Add(Component->GetRelativeTransform());
				}
			}
		}
	}
	/*/
	UStaticMeshComponent* Component = Cast<UStaticMeshComponent>(Sub);
	if (Component) {
		if (Component->GetStaticMesh()) {
			Meshes.Add(Component->GetStaticMesh());
			Transforms.Add(Component->GetRelativeTransform());
		}
	}
	//*/
}


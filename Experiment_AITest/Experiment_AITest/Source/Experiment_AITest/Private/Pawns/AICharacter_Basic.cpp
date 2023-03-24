// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/AICharacter_Basic.h"

// Sets default values
AAICharacter_Basic::AAICharacter_Basic()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAICharacter_Basic::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAICharacter_Basic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


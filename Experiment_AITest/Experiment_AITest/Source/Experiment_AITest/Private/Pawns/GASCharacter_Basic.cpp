// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/GASCharacter_Basic.h"
#include "GAS/AbilitySystemComponent_Basic.h"

// Sets default values
AGASCharacter_Basic::AGASCharacter_Basic()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GASComponent = CreateDefaultSubobject<UAbilitySystemComponent_Basic>(TEXT("GAS Component"));
}

// Called when the game starts or when spawned
void AGASCharacter_Basic::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGASCharacter_Basic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGASCharacter_Basic::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


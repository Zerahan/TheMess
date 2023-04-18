// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AITestPlayerController.h"
#include "Interfaces/FactionInterface.h"
#include "GameFramework/GameStateBase.h"

AAITestPlayerController::AAITestPlayerController()
	: Super()
{
	MyFaction = EFaction::Faction1;
}

void AAITestPlayerController::BeginPlay()
{
	AGameStateBase* GameState = GetWorld()->GetGameState();
	IFactionInterface* FactionInterface = Cast<IFactionInterface>(GameState);
	if (FactionInterface) {
		FactionInterface->Execute_AssignControllerToFaction(GameState, this, MyFaction);
	}
	Super::BeginPlay();
}

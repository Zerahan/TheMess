// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game/AgoraGameMode.h"
#include "Characters/PlayerCameraPawn.h"

AAgoraGameMode::AAgoraGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = APlayerCameraPawn::StaticClass();	
}

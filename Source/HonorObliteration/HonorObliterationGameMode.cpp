// Copyright Epic Games, Inc. All Rights Reserved.

#include "HonorObliterationGameMode.h"
#include "HonorObliterationCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHonorObliterationGameMode::AHonorObliterationGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (DefaultPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = DefaultPawnBPClass.Class;
	}

	numRounds = 3;
	roundTime = 20;
	isTimerActive = false;
}


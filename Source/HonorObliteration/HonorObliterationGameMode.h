// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HonorObliterationCharacter.h"
#include "HonorObliterationGameMode.generated.h"



UCLASS(minimalapi)
class AHonorObliterationGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AHonorObliterationGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Reference")
		AHonorObliterationCharacter* Player1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Reference")
		AHonorObliterationCharacter* Player2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "round")
		float roundTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "round")
		int numRounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "round")
		bool isTimerActive;

};





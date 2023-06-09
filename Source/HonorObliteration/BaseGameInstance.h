// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	VE_Default		UMETA(DisplayName = "Mannequin"),
	VE_Boss			UMETA(DisplayName = "Boss"),
	VE_Countess		UMETA(DisplayName = "Countess")
};

UCLASS()
class HONOROBLITERATION_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Reference")
		ECharacterClass characterClassP1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Reference")
		ECharacterClass characterClassP2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "controller")
		bool isDeviceForMultiplayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Instance Round")
		float roundTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Instance Round")
		int numRounds;
};

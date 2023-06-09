// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HonorObliterationCharacter.h"
#include "MyHonorObliterationPlayer.generated.h"


UCLASS()
class HONOROBLITERATION_API AMyHonorObliterationPlayer : public AHonorObliterationCharacter
{
	GENERATED_BODY()

public :

	AMyHonorObliterationPlayer();

protected :

	virtual void BeginPlay() override; 

public :

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};

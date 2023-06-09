// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHonorObliterationPlayer.h"

AMyHonorObliterationPlayer::AMyHonorObliterationPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyHonorObliterationPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AMyHonorObliterationPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyHonorObliterationPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
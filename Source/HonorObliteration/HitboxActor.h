// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HitboxActor.generated.h"

UENUM(BlueprintType)
enum class EHitboxEnum : uint8
{
	HB_PROXIMITY UMETA(DisplayName = "procimity"),
	HB_STRIKE UMETA(DisplayName = "Strike"),
	HB_HURTBOX UMETA(DisplayName = "hurtbox")
};

UCLASS()
class HONOROBLITERATION_API AHitboxActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHitboxActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void TriggerVisualizeHitbox();

	UFUNCTION(BlueprintImplementableEvent)
		void VisualizeHitbox();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float hitboxDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float hitStunTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float blockStunTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float pushBackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float launchDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		EHitboxEnum hitboxType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		FVector hitboxLocation; 
		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



};

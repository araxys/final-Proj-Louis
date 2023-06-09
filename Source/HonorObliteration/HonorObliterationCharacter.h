// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameInstance.h"
#include "GameFramework/Character.h"
#include "HonorObliterationCharacter.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	VE_Default		UMETA(DisplayName = "NOT_MOVING"),
	VE_MovingRight	UMETA(DisplayName = "MOVING_RIGHT"),
	VE_RunningRight	UMETA(DisplayName = "RUNNING_RIGHT"),
	VE_MovingLeft	UMETA(DisplayName = "MOVING_LEFT"),
	VE_RunningLeft	UMETA(DisplayName = "RUNNING_LEFT"),
	VE_Jumping      UMETA(DisplayName = "JUMPING"),
	VE_Stunned      UMETA(DisplayName = "STUNNED"),
	VE_Blocking		UMETA(DisplayName = "BLOCKING"),
	VE_Crouching	UMETA(DisplayName = "CROUCHING"),
	VE_Launched		UMETA(DisplayName = "LAUNCHED")
};

UCLASS(config=Game)
class AHonorObliterationCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* CameraBoom;

	void StartAttack1();
	void StartAttack2();
	void StartAttack3();
	void StartAttack4();
	void StartExceptionnalAttack();

	UFUNCTION(BlueprintCallable)
		void P2KeyBoardAttack1();

	UFUNCTION(BlueprintCallable)
		void P2KeyBoardAttack2();

	UFUNCTION(BlueprintCallable)
		void P2KeyBoardAttack3();

	UFUNCTION(BlueprintCallable)
		void P2KeyBoardAttack4();

	UFUNCTION(BlueprintCallable)
		void P2KeyBoardExceptionnalAttack();

	UFUNCTION(BlueprintCallable)
		void P2KeyBoardJump();

	UFUNCTION(BlueprintCallable)
		void P2KeyBoardStopJumping();

	UFUNCTION(BlueprintCallable)
		void P2KeyBoardMoveRight(float Value);
	

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual void Tick(float DeltaTime) override;

	virtual void Jump() override;
	virtual void StopJumping() override;
	virtual void Landed(const FHitResult& Hit) override;

	UFUNCTION(BlueprintCallable)
		void StartCrouching();

	UFUNCTION(BlueprintCallable)
		void StopCrouching();

	UFUNCTION(BlueprintCallable)
		void startBlocking();

	UFUNCTION(BlueprintCallable)
		void stopBlocking();

	UFUNCTION(BlueprintCallable)
		void CollideWithProximityHitbox();

	UFUNCTION(BlueprintCallable)
		void WinRound();

	UFUNCTION(BlueprintCallable)
		void WinMatch();

	UFUNCTION(BlueprintImplementableEvent)
		void AddInputIconToscreen(int _iconIndex, bool _ShouldAddInput = true);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void notifyRoundStart();

	UFUNCTION(BlueprintImplementableEvent)
		void notifyRoundEnd();

	UFUNCTION(BlueprintImplementableEvent)
		void UptdateHUDRoundIcons();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		AActor* hurtbox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		ECharacterState characterState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Reference")
		AHonorObliterationCharacter* otherPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
		FTransform transform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
		FVector scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
		bool isFlipped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attack")
		bool hasLandHit;

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float _damageAmount, float _hitStunTime, float _blockStunTime, float _pushBackAmount, float _launchAmount);

	void PerformPushBack(float _pushBackAmount, float _launchAmount, bool _hasBlocked);

	void BeginStun();

	void EndStun();

	FTimerHandle StunTimeHandle;

	// The amount of health the character currently has
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float playerHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "camera")
		float maxDistanceApart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float StunTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float gravityScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "super meter")
		float superMeterAmount;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attack")
		bool wasLightAttackUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attack")
		bool wasLightExAttackUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attack")
		bool wasMediumAttackUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attack")
		bool wasMediumExAttackUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attack")
		bool wasHeavyAttackUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attack")
		bool wasHeavyExAttackUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attack")
		bool wasSuperUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attack")
		bool canUseExAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attack")
		bool canMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "controller")
		bool isDeviceForMultiplayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "animations")
		bool isReadyForEntrance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "animations")
		bool hasLostRound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "animations")
		bool hasWinMatch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "game logic")
		int roundsWon;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		//bool isCrouching;

public:
	AHonorObliterationCharacter();

	/** Returns SideViewCameraComponent subobject **/
	//FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};

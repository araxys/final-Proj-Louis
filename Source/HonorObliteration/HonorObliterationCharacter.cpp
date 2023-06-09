// Copyright Epic Games, Inc. All Rights Reserved.


#include "HonorObliterationCharacter.h"
#include "HonorObliterationGameMode.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AHonorObliterationCharacter::AHonorObliterationCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->SetUsingAbsoluteRotation(true); 
	 
	// Rotation of the character should not affect rotation of boom
	//CameraBoom->bDoCollisionTest = false;
	//CameraBoom->TargetArmLength = 500.f;
	//CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	//CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	//SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	//SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	
	//we dont want the controler rotating the camera
	//SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	otherPlayer = nullptr;
	hurtbox = nullptr;

	characterState = ECharacterState::VE_Default;
	transform = FTransform();
	scale = FVector();

	playerHealth = 1.00f;
	maxDistanceApart = 800.0f;
	StunTime = 0.0f;
	gravityScale = GetCharacterMovement()->GravityScale;
	superMeterAmount = 0.00f;

	roundsWon = 0;

	wasLightAttackUsed = false;
	wasMediumAttackUsed = false;
	wasHeavyAttackUsed = false;
	wasSuperUsed = false;
	wasLightExAttackUsed = false;
	wasMediumExAttackUsed = false;
	wasHeavyExAttackUsed = false;
	canUseExAttack = false;

	isFlipped = false;
	hasLandHit = false;	
	canMove = true;

	isReadyForEntrance = false;
	hasLostRound = false;
	hasWinMatch = false;
	
}

//////////////////////////////////////////////////////////////////////////
// Input

void AHonorObliterationCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (auto gameMode = Cast<AHonorObliterationGameMode>(GetWorld()->GetAuthGameMode()))
	{
		if (gameMode->Player1 == this)
		{
			UE_LOG(LogTemp, Warning, TEXT("Player 1 has bound their controls."))

			// set up gameplay key bindings
			PlayerInputComponent->BindAction("JumpP1", IE_Pressed, this, &AHonorObliterationCharacter::Jump);
			PlayerInputComponent->BindAction("JumpP1", IE_Released, this, &AHonorObliterationCharacter::StopJumping);

			PlayerInputComponent->BindAction("CrouchP1", IE_Pressed, this, &AHonorObliterationCharacter::StartCrouching);
			PlayerInputComponent->BindAction("CrouchP1", IE_Released, this, &AHonorObliterationCharacter::StopCrouching);

			PlayerInputComponent->BindAction("BlockP1", IE_Pressed, this, &AHonorObliterationCharacter::startBlocking);
			PlayerInputComponent->BindAction("BlockP1", IE_Released, this, &AHonorObliterationCharacter::stopBlocking);


			PlayerInputComponent->BindAxis("MoveRightP1", this, &AHonorObliterationCharacter::MoveRight);

			PlayerInputComponent->BindAction("attack1P1", IE_Pressed, this, &AHonorObliterationCharacter::StartAttack1);
			PlayerInputComponent->BindAction("attack2P1", IE_Pressed, this, &AHonorObliterationCharacter::StartAttack2);
			PlayerInputComponent->BindAction("attack3P1", IE_Pressed, this, &AHonorObliterationCharacter::StartAttack3);
			PlayerInputComponent->BindAction("attack4P1", IE_Pressed, this, &AHonorObliterationCharacter::StartAttack4);
			

			PlayerInputComponent->BindAction("ExceptionnalAttackP1", IE_Pressed, this, &AHonorObliterationCharacter::StartExceptionnalAttack);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Player 2 has bound their controls."))

			PlayerInputComponent->BindAction("JumpP2", IE_Pressed, this, &AHonorObliterationCharacter::Jump);
			PlayerInputComponent->BindAction("JumpP2", IE_Released, this, &AHonorObliterationCharacter::StopJumping);

			PlayerInputComponent->BindAction("CrouchP2", IE_Pressed, this, &AHonorObliterationCharacter::StartCrouching);
			PlayerInputComponent->BindAction("CrouchP2", IE_Released, this, &AHonorObliterationCharacter::StopCrouching);

			PlayerInputComponent->BindAction("BlockP2", IE_Pressed, this, &AHonorObliterationCharacter::startBlocking);
			PlayerInputComponent->BindAction("BlockP2", IE_Released, this, &AHonorObliterationCharacter::stopBlocking);


			PlayerInputComponent->BindAxis("MoveRightP2", this, &AHonorObliterationCharacter::MoveRight);

			PlayerInputComponent->BindAction("attack1P2", IE_Pressed, this, &AHonorObliterationCharacter::StartAttack1);
			PlayerInputComponent->BindAction("attack2P2", IE_Pressed, this, &AHonorObliterationCharacter::StartAttack2);
			PlayerInputComponent->BindAction("attack3P2", IE_Pressed, this, &AHonorObliterationCharacter::StartAttack3);
			PlayerInputComponent->BindAction("attack4P2", IE_Pressed, this, &AHonorObliterationCharacter::StartAttack4);

			PlayerInputComponent->BindAction("ExceptionnalAttackP2", IE_Pressed, this, &AHonorObliterationCharacter::StartExceptionnalAttack);

		}
	}
}

void AHonorObliterationCharacter::Jump()
{
	if (canMove == true)
	
		ACharacter::Jump();
		characterState = ECharacterState::VE_Jumping;
	}


void AHonorObliterationCharacter::StopJumping()
{
	ACharacter::StopJumping();
}

void AHonorObliterationCharacter::Landed(const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("landed"));

	if (characterState == ECharacterState::VE_Launched || characterState == ECharacterState::VE_Jumping)
	{
		GetCharacterMovement()->GravityScale = gravityScale;
		characterState = ECharacterState::VE_Default;
	}
}

void AHonorObliterationCharacter::StartCrouching()
{
	characterState = ECharacterState::VE_Crouching;
}

void AHonorObliterationCharacter::StopCrouching()
{
	characterState = ECharacterState::VE_Default;
}

void AHonorObliterationCharacter::startBlocking()
{
	characterState = ECharacterState::VE_Blocking;
}

void AHonorObliterationCharacter::stopBlocking()
{
	characterState = ECharacterState::VE_Default;
}

void AHonorObliterationCharacter::MoveRight(float Value)
{

	if (canMove && characterState != ECharacterState::VE_Crouching && characterState != ECharacterState::VE_Blocking)
	{
		if (characterState != ECharacterState::VE_Jumping && characterState != ECharacterState::VE_Launched)
		{
			if (Value > 0.20f)
			{
				characterState = ECharacterState::VE_MovingRight;
			}
			else if (Value < -0.20f)
			{
				characterState = ECharacterState::VE_MovingLeft;
			}
			else
			{
				characterState = ECharacterState::VE_Default;
			}
		}

			float currentDistanceApart = abs(otherPlayer->GetActorLocation().Y - GetActorLocation().Y);

			if (currentDistanceApart >= maxDistanceApart)
			{
				if ((currentDistanceApart + Value < currentDistanceApart && !isFlipped) || (currentDistanceApart - Value < currentDistanceApart && isFlipped))
				{
					AddMovementInput(FVector(0.f, 1.f, 0.f), Value);
				}
			}
			else
			{
				AddMovementInput(FVector(0.f, 1.f, 0.f), Value);
			}
	}
}

void AHonorObliterationCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void AHonorObliterationCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void AHonorObliterationCharacter::StartAttack1()
{
	UE_LOG(LogTemp, Warning, TEXT("c'est la première attaque"));
	wasLightAttackUsed = true;
}

void AHonorObliterationCharacter::StartAttack2()
{
	UE_LOG(LogTemp, Warning, TEXT("c'est la deuxième attaque"));
	wasMediumAttackUsed = true;
}

void AHonorObliterationCharacter::StartAttack3()
{
	UE_LOG(LogTemp, Warning, TEXT("c'est la troisième attaque"));
	wasHeavyAttackUsed = true;
}

void AHonorObliterationCharacter::StartAttack4()
{
	if (superMeterAmount >= 0.00f)
	{
		UE_LOG(LogTemp, Warning, TEXT("c'est la quatrième attaque"));
		wasSuperUsed = true;
	}
}

void AHonorObliterationCharacter::StartExceptionnalAttack()
{
	if (wasLightAttackUsed && superMeterAmount >= 0.20f && canUseExAttack)
	{
		wasLightExAttackUsed = true;
		superMeterAmount -= 0.20f;
	}
	else if (wasMediumAttackUsed && superMeterAmount >= 0.35f && canUseExAttack)
	{
		wasMediumExAttackUsed = true;
		superMeterAmount -= 0.35f;
	}
	else if (wasHeavyAttackUsed && superMeterAmount >= 0.50f && canUseExAttack)
	{
		wasHeavyExAttackUsed = true;
		superMeterAmount -= 0.50f;
	}

	if (superMeterAmount < 0.00f)
	{
		superMeterAmount = 0.00f;
	}
}

void AHonorObliterationCharacter::P2KeyBoardAttack1()
{
	StartAttack1();
}

void AHonorObliterationCharacter::P2KeyBoardAttack2()
{
	StartAttack2();
}

void AHonorObliterationCharacter::P2KeyBoardAttack3()
{
	StartAttack3();
}

void AHonorObliterationCharacter::P2KeyBoardAttack4()
{
	StartAttack4();
}

void AHonorObliterationCharacter::P2KeyBoardExceptionnalAttack()
{
	StartExceptionnalAttack();
}

void AHonorObliterationCharacter::P2KeyBoardJump()
{
	Jump();
}

void AHonorObliterationCharacter::P2KeyBoardStopJumping()
{
	StopJumping();
}

void AHonorObliterationCharacter::P2KeyBoardMoveRight(float Value)
{
	MoveRight(Value);
} 

void AHonorObliterationCharacter::CollideWithProximityHitbox()
{
	if ((characterState == ECharacterState::VE_MovingLeft && !isFlipped) || (characterState == ECharacterState::VE_MovingRight && isFlipped))
	{
		UE_LOG(LogTemp, Warning, TEXT("the character is auto blocking"));
		characterState = ECharacterState::VE_Blocking;
	}
}

void AHonorObliterationCharacter::PerformPushBack(float _pushBackAmount, float _launchAmount, bool _hasBlocked)
{
	if (_hasBlocked)
	{
		if (isFlipped)
		{
			LaunchCharacter(FVector(0.0f, -_pushBackAmount * 2.0f, 0.0f), false, false);
		}
		else
		{
			LaunchCharacter(FVector(0.0f, _pushBackAmount * 2.0f, 0.0f), false, false);
		}
	}
	else
	{
			if (_launchAmount > 0.0f)
			{
				GetCharacterMovement()->GravityScale *= 0.7;
				characterState = ECharacterState::VE_Launched;
			}

			if (isFlipped)
			{
				LaunchCharacter(FVector(0.0f, -_pushBackAmount, _launchAmount), false, false);

			}
			else
			{
				LaunchCharacter(FVector(0.0f, _pushBackAmount, _launchAmount), false, false);
			}
	}
}

void AHonorObliterationCharacter::TakeDamage(float _damageAmount, float _hitStunTime, float _blockStunTime, float _pushBackAmount, float _launchAmount)
{
	if (characterState != ECharacterState::VE_Blocking)
	{
		UE_LOG(LogTemp, Warning, TEXT("we are taking damage for %f points."), _damageAmount);
		playerHealth -= _damageAmount;
		superMeterAmount += _damageAmount * 0.85f;

		StunTime = _hitStunTime;

		if (StunTime > 0.0f)
		{
			characterState = ECharacterState::VE_Stunned;
			BeginStun();
		}	

		if (otherPlayer)
		{
			otherPlayer->hasLandHit = true;
			otherPlayer->PerformPushBack(_pushBackAmount, 0.0f, false);

			if (!otherPlayer->wasLightAttackUsed)
			{
				otherPlayer->superMeterAmount += _damageAmount * 0.30f;
			}
		}

		PerformPushBack(_pushBackAmount, _launchAmount, false);
	}
	else
	{
		float reduceDamage = _damageAmount * 0.5F;
		UE_LOG(LogTemp, Warning, TEXT("We are taking reduced damage for %f points"), reduceDamage);
		playerHealth -= reduceDamage;

		StunTime = _blockStunTime;

		if (StunTime > 0.0f)
		{
			BeginStun();
		}
		else
		{
			characterState = ECharacterState::VE_Default;
		}

		if (otherPlayer)
		{
			otherPlayer->hasLandHit = false;
			otherPlayer->PerformPushBack(_pushBackAmount, 0.0f, false);
		}

		PerformPushBack(_pushBackAmount, 0.0f, true);
	}


	if (playerHealth < 0.00f)
	{
		playerHealth = 0.00f;
	}
}

void AHonorObliterationCharacter::BeginStun()
{
	canMove = false;
	GetWorld()->GetTimerManager().SetTimer(StunTimeHandle, this, &AHonorObliterationCharacter::EndStun, StunTime, false);
}

void AHonorObliterationCharacter::EndStun()
{
	if (characterState != ECharacterState::VE_Launched)
	{
		characterState = ECharacterState::VE_Default;
	}

	canMove = true;
}
 
void AHonorObliterationCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (characterState != ECharacterState::VE_Jumping)
	{
		if (otherPlayer)
		{
			if (auto characterMovement = GetCharacterMovement())
			{
				if (auto enemyMovement = otherPlayer->GetCharacterMovement())
				{
					if (enemyMovement->GetActorLocation().Y <= characterMovement->GetActorLocation().Y)
					{
						if (isFlipped)
						{
							if (auto mesh = GetCapsuleComponent()->GetChildComponent(1))
							{
								transform = mesh->GetRelativeTransform();
								scale = transform.GetScale3D();
								scale.Y = -1;
								transform.SetScale3D(scale);
								mesh->SetRelativeTransform(transform);
							}
							isFlipped = false;
						}
					}
					else
					{
						if (!isFlipped)
						{
							if (auto mesh = GetCapsuleComponent()->GetChildComponent(1))
							{
								transform = mesh->GetRelativeTransform();
								scale = transform.GetScale3D();
								scale.Y = 1;
								transform.SetScale3D(scale);
								mesh->SetRelativeTransform(transform);
							}
							isFlipped = true;
						}
					}
				}
			}
		}
	}
}

void AHonorObliterationCharacter::WinRound()
{
	otherPlayer->hasLostRound = true;
	++roundsWon;

	notifyRoundEnd();
	UptdateHUDRoundIcons();
}

void AHonorObliterationCharacter::WinMatch()
{
	canMove = false;
	hasWinMatch = true;
}

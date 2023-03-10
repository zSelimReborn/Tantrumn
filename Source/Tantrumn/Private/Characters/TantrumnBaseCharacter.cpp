// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TantrumnBaseCharacter.h"

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/FallHandlerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ATantrumnBaseCharacter::ATantrumnBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(GetRootComponent());

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(CameraBoom);

	FallHandlerComponent = CreateDefaultSubobject<UFallHandlerComponent>(TEXT("Fall Handler Component"));
}

// Called when the game starts or when spawned
void ATantrumnBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem* EnhancedInputComponent = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
		if (EnhancedInputComponent)
		{
			EnhancedInputComponent->AddMappingContext(MappingContext, 0);
		}
	}

	if (GetCharacterMovement())
	{
		InitialWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	}

	FallHandlerComponent->OnFallDamage().AddDynamic(this, &ATantrumnBaseCharacter::OnFallDamage);
}

// Called every frame
void ATantrumnBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATantrumnBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATantrumnBaseCharacter::OnFallDamage(const float FallRatio)
{
	UE_LOG(LogTemp, Error, TEXT("Ouch! %.2f"), FallRatio);
}

float ATantrumnBaseCharacter::GetLookUpRate() const
{
	return BaseLookUpRate;
}

float ATantrumnBaseCharacter::GetLookRightRate() const
{
	return BaseLookRightRate;
}

void ATantrumnBaseCharacter::RequestSprintAction()
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void ATantrumnBaseCharacter::RequestWalkAction()
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = InitialWalkSpeed;
	}
}


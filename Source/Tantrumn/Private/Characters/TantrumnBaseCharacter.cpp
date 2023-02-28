// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TantrumnBaseCharacter.h"

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
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


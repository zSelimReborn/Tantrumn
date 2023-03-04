// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/TantrumnPlayerController.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void ATantrumnPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
		if (EnhancedInputComponent)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ATantrumnPlayerController::RequestJumpAction);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ATantrumnPlayerController::RequestStopJumpAction);
			
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATantrumnPlayerController::RequestMoveAction);
			
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATantrumnPlayerController::RequestLookAction);

			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ATantrumnPlayerController::RequestSprintAction);
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ATantrumnPlayerController::RequestCancelSprintAction);

			EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ATantrumnPlayerController::RequestCrouchAction);
		}
	}
}

void ATantrumnPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetCharacter() && GetCharacter()->GetCharacterMovement())
	{
		WalkSpeed = GetCharacter()->GetCharacterMovement()->MaxWalkSpeed;
	}
}

void ATantrumnPlayerController::RequestJumpAction()
{
 	if (GetCharacter())
	{
		GetCharacter()->Jump();
	}
}

void ATantrumnPlayerController::RequestStopJumpAction()
{
	if (GetCharacter())
	{
		GetCharacter()->StopJumping();
	}
}

void ATantrumnPlayerController::RequestMoveAction(const FInputActionValue& Value)
{
	if (GetCharacter())
	{
		const FRotator CurrentRotation = GetControlRotation();
		const FVector2d MoveDirection = Value.Get<FVector2d>();

		const float ForwardAxisValue = MoveDirection.X;
		const float RightAxisValue = MoveDirection.Y;

		GetCharacter()->AddMovementInput(FRotationMatrix{CurrentRotation}.GetScaledAxis(EAxis::X), ForwardAxisValue);
		GetCharacter()->AddMovementInput(FRotationMatrix{CurrentRotation}.GetScaledAxis(EAxis::Y), RightAxisValue);
	}
}

void ATantrumnPlayerController::RequestLookAction(const FInputActionValue& Value)
{
	if (GetCharacter())
	{
		const FVector2d LookVector = Value.Get<FVector2d>();
		const float PitchAxisValue = LookVector.Y;
		const float YawAxisValue = LookVector.X;
		
		GetCharacter()->AddControllerPitchInput(PitchAxisValue * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
		GetCharacter()->AddControllerYawInput(YawAxisValue * BaseLookRightRate * GetWorld()->GetDeltaSeconds());
	}
}

void ATantrumnPlayerController::RequestSprintAction()
{
	if (GetCharacter() && GetCharacter()->GetCharacterMovement())
	{
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void ATantrumnPlayerController::RequestCancelSprintAction()
{
	if (GetCharacter() && GetCharacter()->GetCharacterMovement())
	{
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

void ATantrumnPlayerController::RequestCrouchAction()
{
	if (!GetCharacter() || !GetCharacter()->GetCharacterMovement())
	{
		return;
	}
	
	if (!GetCharacter()->GetCharacterMovement()->IsMovingOnGround())
	{
		return;
	}
	
	if (!GetCharacter()->GetCharacterMovement()->IsCrouching())
	{
		GetCharacter()->Crouch();
	}
	else
	{
		GetCharacter()->UnCrouch();
	}
}

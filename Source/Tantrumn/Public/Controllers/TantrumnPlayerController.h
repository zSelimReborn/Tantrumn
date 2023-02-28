// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "TantrumnPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class TANTRUMN_API ATantrumnPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;

protected:
	virtual void BeginPlay() override;
	
protected:
	void RequestJumpAction();
	void RequestStopJumpAction();
	void RequestMoveAction(const FInputActionValue&);
	void RequestLookAction(const FInputActionValue&);
	void RequestSprintAction();
	void RequestCancelSprintAction();
	
	// To Tune
protected:
	// Value deg/sec
	UPROPERTY(EditAnywhere, Category="Look")
	float BaseLookUpRate = 90.f;

	// Value deg/sec
	UPROPERTY(EditAnywhere, Category="Look")
	float BaseLookRightRate = 90.f;

	UPROPERTY(EditAnywhere, Category="Sprint", meta=(ClampMin="0", UIMin="0", ForceUnits="cm/s"))
	float SprintSpeed = 900.f;

	UPROPERTY(Transient)
	float WalkSpeed = 600.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> SprintAction;

};

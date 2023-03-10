// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TantrumnBaseCharacter.generated.h"

class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TANTRUMN_API ATantrumnBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATantrumnBaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Movement interface
public:
	float GetLookUpRate() const;
	float GetLookRightRate() const;
	
	virtual void RequestSprintAction();
	virtual void RequestWalkAction();
	
	//Components
protected:
	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<UCameraComponent> FollowCamera;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditAnywhere, Category="Look", meta=(ClampMin="0", UIMin="0", ForceUnits="deg/s"))
	float BaseLookUpRate = 90.f;

	UPROPERTY(EditAnywhere, Category="Look", meta=(ClampMin="0", UIMin="0", ForceUnits="deg/s"))
	float BaseLookRightRate = 90.f;

	UPROPERTY(EditAnywhere, Category="Sprint", meta=(ClampMin="0", UIMin="0", ForceUnits="cm/s"))
	float SprintSpeed = 900.f;

	UPROPERTY(Transient, VisibleAnywhere, Category="Sprint")
	float InitialWalkSpeed = 600.f;
};

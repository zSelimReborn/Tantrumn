// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStatusComponent.generated.h"

UENUM()
enum class EPlayerStatus
{
	EPS_Default		UMETA(DisplayName="Default"),
	EPS_Stunned		UMETA(DisplayName="Stunned")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANTRUMN_API UPlayerStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// Functionalities
public:
	void StartStun(const float& StunRatio);
	void UpdateStun();
	void EndStun();

// Mutators
public:
	FORCEINLINE EPlayerStatus GetPlayerStatus() const { return PlayerStatus; }
	FORCEINLINE bool IsStunned() const { return PlayerStatus == EPlayerStatus::EPS_Stunned; }
	
	FORCEINLINE float GetLookUpRateOnStun() const { return LookUpRateOnStun; }
	FORCEINLINE float GetLookRightRateOnStun() const { return LookRightOnStun; }
	FORCEINLINE float GetWalkSpeedOnStun() const { return WalkSpeedOnStun; }

// Properties
protected:
	UPROPERTY(Transient)
	TObjectPtr<ACharacter> OwnerCharacter;

	UPROPERTY(Transient)
	float InitialWalkSpeed = 600.f;
	
	UPROPERTY(Transient, VisibleAnywhere, Category="Player Status")
	EPlayerStatus PlayerStatus = EPlayerStatus::EPS_Default;

	UPROPERTY(EditAnywhere, Category="Stun", meta=(ClampMin=0.f, ClampMax=1.f))
	float StunPlayerThreshold = 0.5f;

	UPROPERTY(EditAnywhere, Category="Stun")
	float MinStunTime = 1.f;

	UPROPERTY(EditAnywhere, Category="Stun")
	float MaxStunTime = 3.f;

	UPROPERTY(EditAnywhere, Category="Stun")
	float LookUpRateOnStun = 30.f;

	UPROPERTY(EditAnywhere, Category="Stun")
	float LookRightOnStun = 30.f;

	UPROPERTY(EditAnywhere, Category="Stun", meta=(ClampMin="0", UIMin="0", ForceUnits="cm/s"))
	float WalkSpeedOnStun = 200.f;

	UPROPERTY(Transient, VisibleAnywhere, Category="Stun")
	float StunTime = 0.f;

	UPROPERTY(Transient, VisibleAnywhere, Category="Stun")
	float CurrentStunTime = 0.f;
		
};

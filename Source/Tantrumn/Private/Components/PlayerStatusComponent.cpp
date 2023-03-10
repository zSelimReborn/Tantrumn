// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PlayerStatusComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UPlayerStatusComponent::UPlayerStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter)
	{
		InitialWalkSpeed = OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed;
	}
}


// Called every frame
void UPlayerStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateStun();
}

void UPlayerStatusComponent::StartStun(const float& StunRatio)
{
	if (PlayerStatus == EPlayerStatus::EPS_Stunned)
	{
		return;
	}

	if (StunRatio < StunPlayerThreshold)
	{
		return;
	}
	
	const float StunDelta = MaxStunTime - MinStunTime;
	StunTime = MinStunTime + (StunRatio * StunDelta);
	CurrentStunTime = 0.f;
	PlayerStatus = EPlayerStatus::EPS_Stunned;

	if (OwnerCharacter)
	{
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = WalkSpeedOnStun;
	}
}

void UPlayerStatusComponent::UpdateStun()
{
	if (PlayerStatus != EPlayerStatus::EPS_Stunned)
	{
		return;
	}
	
	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	CurrentStunTime += DeltaTime;
	const bool bIsStunned = CurrentStunTime < StunTime;
	if (bIsStunned)
	{
		PlayerStatus = EPlayerStatus::EPS_Stunned;
	}
	else
	{
		PlayerStatus = EPlayerStatus::EPS_Default;
		EndStun();
	}
}

void UPlayerStatusComponent::EndStun()
{
	StunTime = 0.f;
	CurrentStunTime = 0.f;

	if (OwnerCharacter)
	{
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = InitialWalkSpeed;
	}
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FallHandlerComponent.h"

#include "GameFramework/Character.h"

// Sets default values for this component's properties
UFallHandlerComponent::UFallHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UFallHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter)
	{
		OwnerCharacter->LandedDelegate.AddDynamic(this, &UFallHandlerComponent::OnCharacterLanded);

		OwnerPC = Cast<APlayerController>(OwnerCharacter->GetController());
	}
}

void UFallHandlerComponent::OnCharacterLanded(const FHitResult& Hit)
{
	if (GetOwner() == nullptr)
	{
		return;
	}
	
	const float FallImpactSpeed = FMath::Abs(GetOwner()->GetVelocity().Z);
	if (FallImpactSpeed < MinImpact)
	{
		return;
	}

	const float DeltaImpact = MaxImpact - MinImpact;
	const float FallRatio = FMath::Clamp((FallImpactSpeed - MinImpact) / DeltaImpact, 0.f, 1.f);

	const bool bAffectSmall = (FallRatio <= RumbleLargeThreshold);
	const bool bAffectLarge = (FallRatio > RumbleLargeThreshold);

	if (OwnerPC)
	{
		OwnerPC->PlayDynamicForceFeedback(
			FallRatio,
			RumbleDuration,
			bAffectLarge,
			bAffectSmall,
			bAffectLarge,
			bAffectSmall
		);
	}

	OnFallDamageEvent.Broadcast(FallRatio);
}


// Called every frame
void UFallHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


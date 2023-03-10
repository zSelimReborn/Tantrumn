// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FallHandlerComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFallDamage, const float, FallRatio);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANTRUMN_API UFallHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFallHandlerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnCharacterLanded(const FHitResult& Hit);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FOnFallDamage& OnFallDamage() { return OnFallDamageEvent; };

protected:
	UPROPERTY(Transient)
	TObjectPtr<ACharacter> OwnerCharacter;

	UPROPERTY(Transient)
	TObjectPtr<APlayerController> OwnerPC;

	FOnFallDamage OnFallDamageEvent;

	UPROPERTY(EditAnywhere, Category="Fall Impact|Speed")
	float MinImpact = 600.f;

	UPROPERTY(EditAnywhere, Category="Fall Impact|Speed")
	float MaxImpact = 1500.f;

	UPROPERTY(EditAnywhere, Category="Fall Impact|Rumble", meta=(ClampMin=0.f, ClampMax=1.f))
	float RumbleLargeThreshold = 0.5f;

	UPROPERTY(EditAnywhere, Category="Fall Impact|Rumble", meta=(ClampMin=0.f, ClampMax=1.f))
	float RumbleDuration = 0.5f;
};


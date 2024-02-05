// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "HIGrenade.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGrenadeEndLaunch);

UCLASS()
class HOWLOFIRON_API AHIGrenade : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHIGrenade();

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Grenade")
		UProjectileMovementComponent* projectileMovement;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Grenade")
		UStaticMeshComponent* grenadeMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grenade")
		URotatingMovementComponent* rotatingMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grenade")
		bool objetiveSetted;

	FOnGrenadeEndLaunch onGrenadeEndLaunch;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetGrenadeObjective(FVector objetivePosition);
};

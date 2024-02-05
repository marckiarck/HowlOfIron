// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Weapons/HIGrenade.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AHIGrenade::AHIGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	objetiveSetted = false;

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("projectileMovement");
	rotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>("rotatingMovement");
	rotatingMovement->Deactivate();

	grenadeMesh = CreateDefaultSubobject<UStaticMeshComponent>("grenadeMesh");
	grenadeMesh->SetSimulatePhysics(false);
}

// Called every frame
void AHIGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ( objetiveSetted && projectileMovement->Velocity == FVector(0.f, 0.f, 0.f))
	{
		grenadeMesh->SetSimulatePhysics(true);
		rotatingMovement->Deactivate();
		onGrenadeEndLaunch.Broadcast();
	}
}


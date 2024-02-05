// Fill out your copyright notice in the Description page of Project Settings.


#include "MapLogic/HITeleportPawn.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

AHITeleportPawn::AHITeleportPawn(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	GetCollisionComponent()->SetCollisionProfileName("NoCollision");
	GetMeshComponent()->SetStaticMesh(nullptr);
	Cast<UFloatingPawnMovement>(MovementComponent)->MaxSpeed = 5000.f;
}
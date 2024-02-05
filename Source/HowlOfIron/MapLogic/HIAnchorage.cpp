// Fill out your copyright notice in the Description page of Project Settings.


#include "MapLogic/HIAnchorage.h"
#include "Components/BoxComponent.h"
#include "HIMacros.h"

AHIAnchorage::AHIAnchorage()
{
	sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(sceneComponent);

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	boxComponent->SetupAttachment(sceneComponent);
	FVector scale = FVector(1.f, 1.f, 1.f);
	boxComponent->SetRelativeScale3D(scale);
	boxComponent->SetCollisionResponseToChannel(GAME_TRACE_ANCHORAGE, ECR_Block);
	//boxComponent->SetCollisionProfileName(FName(TEXT("Wall")));
	//boxComponent->SetNotifyRigidBodyCollision(true);
}


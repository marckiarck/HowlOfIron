// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Conditions/HIConditionRegister.h"

AHIConditionRegister* AHIConditionRegister::instance = nullptr;

// Sets default values
AHIConditionRegister::AHIConditionRegister()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}


// Called every frame
void AHIConditionRegister::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UHIConditionConfiguration*> newRegisteredConditions;
	registeredCoditions.Append(newConditions);
	newConditions.Empty();

	for (UHIConditionConfiguration* conditionConfiguration : registeredCoditions)
	{
		bool conditionResult = conditionConfiguration->condition->HICheckCondition();

		if (conditionResult == false)
		{
			newRegisteredConditions.Add(conditionConfiguration);
		}
		else
		{
			if (conditionConfiguration->meetOnce == false)
			{
				newRegisteredConditions.Add(conditionConfiguration);
			}
		}

	}

	registeredCoditions = newRegisteredConditions;
}

void AHIConditionRegister::BeginPlay()
{
	Super::BeginPlay();
}

AHIConditionRegister* AHIConditionRegister::HIGetConditionRegister()
{
	if (instance == nullptr || instance->IsValidLowLevel() == false)
	{
		FVector aparitionLocation;
		instance = Cast<AHIConditionRegister>(UHIGameData::HIGetWerewolfWorld()->SpawnActor(AHIConditionRegister::StaticClass(), &aparitionLocation));
	}

	return instance;
}

void AHIConditionRegister::HIResetConditionRegister()
{
	instance = nullptr;
}

void AHIConditionRegister::HIRegisterCondition(UHICondition* registeredCondition, bool meetOnce, bool initializeCondition)
{
	UHIConditionConfiguration* conditionConfiguration = NewObject<UHIConditionConfiguration>();
	conditionConfiguration->condition = registeredCondition;
	conditionConfiguration->meetOnce = meetOnce;

	if (initializeCondition)
	{
		conditionConfiguration->condition->HIInitialize();
	}

	newConditions.Add(conditionConfiguration);
}


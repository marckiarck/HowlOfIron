// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/Boss/HILifeConditionComponent.h"
#include <AbilitySystemInterface.h>
#include <AbilitySystemComponent.h>

// Sets default values for this component's properties
UHILifeConditionComponent::UHILifeConditionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHILifeConditionComponent::BeginPlay()
{
	Super::BeginPlay();

	ownerAbilitySystem = Cast<IAbilitySystemInterface>(GetOwner())->GetAbilitySystemComponent();

	for (UHIBossLifeContext* lifeCondition : lifeConditions)
	{
		lifeCondition->HIInitializeContext();
	}
}


// Called every frame
void UHILifeConditionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (UHIBossLifeContext* lifeCondition : lifeConditions)
	{
		lifeCondition->HICheckLifeCondition(ownerAbilitySystem);
	}
}

void UHIBossLifeContext::HICheckLifeCondition(UAbilitySystemComponent* abilitySystem)
{
	if (conditionMet == false)
	{
		if (lifeCondition->HICheckCondition())
		{
			FGameplayEffectContextHandle effectContextHandle;
			abilitySystem->ApplyGameplayEffectToSelf(appliedGameplayEffect, 0.f, effectContextHandle);

			conditionMet = true;
		}
	}
}

void UHIBossLifeContext::HIInitializeContext()
{
	appliedGameplayEffect = Cast<UGameplayEffect>(gameplayEffectClass->GetDefaultObject());
	lifeCondition->HIInitialize();
	conditionMet = false;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HISlomo.h"
#include <GameFramework/WorldSettings.h>

UHISlomo::UHISlomo()
{
	bTickingTask = true;
}

UHISlomo* UHISlomo::HISetTimeScale(UGameplayAbility* OwningAbility, float _newTimeScale, float _scaleDuration)
{
	UHISlomo* returnedTask = NewAbilityTask<UHISlomo>(OwningAbility);

	returnedTask->timeScale =_newTimeScale;
	returnedTask->scaleDuration = _scaleDuration;

	return returnedTask;
}

void UHISlomo::Activate()
{
	AWorldSettings* worldSettings = GetWorld()->GetWorldSettings();
	previousTimeDilation = worldSettings->GetEffectiveTimeDilation();
	worldSettings->SetTimeDilation(timeScale);

	taskLifeTime = 0.f;
}

void UHISlomo::TickTask(float DeltaTime)
{
	taskLifeTime += DeltaTime * 1.f / timeScale;

	if (taskLifeTime >= scaleDuration)
	{
		OnSlomoEnded.Broadcast();
		EndTask();
	}
}

void UHISlomo::OnDestroy(bool bInOwnerFinished)
{
	AWorldSettings* worldSettings = GetWorld()->GetWorldSettings();
	worldSettings->SetTimeDilation(1.f);

	Super::OnDestroy(bInOwnerFinished);
}

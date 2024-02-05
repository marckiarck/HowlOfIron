// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HIDelegateTickTask.h"

UHIDelegateTickTask::UHIDelegateTickTask()
{
	bTickingTask = true;
}

UHIDelegateTickTask* UHIDelegateTickTask::HIDelegateTemporalTask(UGameplayAbility* OwningAbility, float _delegateDuration, float _delegateCallFrecuency)
{
	UHIDelegateTickTask* delegateTask = NewAbilityTask<UHIDelegateTickTask>(OwningAbility);
	delegateTask->delegateDuration = _delegateDuration;
	delegateTask->delegateCallFrecuency = _delegateCallFrecuency;

	return delegateTask;
}

void UHIDelegateTickTask::Activate()
{
	elapsedDelegateTime = 0.f;
	delegateFrecuencyElapsed = 0.f;
	onStart.Broadcast();
}

void UHIDelegateTickTask::TickTask(float DeltaTime)
{

	if (elapsedDelegateTime < delegateDuration)
	{
		delegateFrecuencyElapsed += DeltaTime;
		elapsedDelegateTime += DeltaTime;

		if (delegateFrecuencyElapsed > delegateCallFrecuency)
		{
			delegateFrecuencyElapsed = delegateFrecuencyElapsed - delegateCallFrecuency;
			delegateFunctionality.Broadcast(elapsedDelegateTime,DeltaTime);
		}
	}
	else 
	{
		onEnd.Broadcast();
		EndTask();
	}

}

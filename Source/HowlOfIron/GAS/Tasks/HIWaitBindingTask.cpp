// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HIWaitBindingTask.h"

UHIWaitBindingTask::UHIWaitBindingTask()
{
	bTickingTask = false;
}

UHIWaitBindingTask* UHIWaitBindingTask::HIWaitBinding(UGameplayAbility* OwningAbility, FName bindingName)
{
	UHIWaitBindingTask* returnedTask = NewAbilityTask<UHIWaitBindingTask>(OwningAbility);
	returnedTask->bindingKey = bindingName;

	return returnedTask;
}

void UHIWaitBindingTask::Activate()
{
	playerController = Cast<APlayerController>(Cast<APawn>(GetAvatarActor())->GetController());
	ensure(playerController);
	functionBinding = playerController->InputComponent->BindAction(bindingKey, IE_Pressed, this, &UHIWaitBindingTask::OnBindUsed);
}

void UHIWaitBindingTask::OnDestroy(bool bInOwnerFinished)
{
	if (bInOwnerFinished)
	{
		playerController->InputComponent->RemoveActionBindingForHandle(functionBinding.GetHandle());
	}

	Super::OnDestroy(bInOwnerFinished);
}

void UHIWaitBindingTask::OnBindUsed()
{
	OnBindingUsed.Broadcast();

	playerController->InputComponent->RemoveActionBindingForHandle(functionBinding.GetHandle());
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HIRemoveLooseTagTask.h"

UHIRemoveLooseTagTask* UHIRemoveLooseTagTask::HIRemoveLooseTags(UGameplayAbility* OwningAbility, FGameplayTagContainer looseTags, UAbilitySystemComponent* affectedAbilitySystem)
{
	UHIRemoveLooseTagTask* returnedTask = NewAbilityTask<UHIRemoveLooseTagTask>(OwningAbility);
	returnedTask->removeTags = looseTags;
	returnedTask->abilitySystem = affectedAbilitySystem;

	return returnedTask;
}

void UHIRemoveLooseTagTask::Activate()
{

	if (abilitySystem == nullptr)
	{
		abilitySystem = Cast<UAbilitySystemComponent>(Cast<IAbilitySystemInterface>(GetAvatarActor())->GetAbilitySystemComponent());
	}

	abilitySystem->RemoveLooseGameplayTags(removeTags);
}

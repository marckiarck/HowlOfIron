// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HIAddLooseTagTask.h"

UHIAddLooseTagTask* UHIAddLooseTagTask::HIAddLooseTags(UGameplayAbility* OwningAbility, FGameplayTagContainer looseTags, UAbilitySystemComponent* affectedAbilitySystem, bool _destroyAtEnd/* = false*/)
{
    UHIAddLooseTagTask* returnedTask = NewAbilityTask<UHIAddLooseTagTask>(OwningAbility);
    returnedTask->addedTags = looseTags;
    returnedTask->abilitySystem = affectedAbilitySystem;
    returnedTask->DestroyAtEnd = _destroyAtEnd;

    return returnedTask;
}

void UHIAddLooseTagTask::Activate()
{

    if (abilitySystem == nullptr)
    {
        abilitySystem = Cast<UAbilitySystemComponent>(Cast<IAbilitySystemInterface>(GetAvatarActor())->GetAbilitySystemComponent());
    }

    abilitySystem->AddLooseGameplayTags(addedTags);
}

void UHIAddLooseTagTask::OnDestroy(bool bInOwnerFinished)
{

    if (DestroyAtEnd)
    {
        abilitySystem->RemoveLooseGameplayTags(addedTags);
    }

    Super::OnDestroy(bInOwnerFinished);

}

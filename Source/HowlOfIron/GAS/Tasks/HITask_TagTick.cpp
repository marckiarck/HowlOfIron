// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HITask_TagTick.h"

UHITask_TagTick::UHITask_TagTick()
{
    bTickingTask = true;
    started = false;
}

UHITask_TagTick* UHITask_TagTick::HITagTickDelegate(UGameplayAbility* OwningAbility, FGameplayTag _tagcheck)
{
    UHITask_TagTick* myObj = NewAbilityTask<UHITask_TagTick>(OwningAbility);
    myObj->tagcheck = _tagcheck;
    return myObj;
}

void UHITask_TagTick::Activate()
{
//     if (tagcheck.GetTagName() == FName("None"))
//     {
//         EndTask();
//     }
    if (!tagcheck.IsValid())
    {
        EndTask();
    }
}

void UHITask_TagTick::TickTask(float DeltaTime)
{



    if (!started)
    {
        if (AbilitySystemComponent->HasMatchingGameplayTag(tagcheck))
        {
            started = true;
            AddedTag.Broadcast();

        }
    }
    else
    {
        if (!AbilitySystemComponent->HasMatchingGameplayTag(tagcheck))
        {
            RemovedTag.Broadcast();
            EndTask();
        }
        else
        {
            Tick.Broadcast(DeltaTime);
        }
    }
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HITask_TagDelegateTime.h"

UHITask_TagDelegateTime::UHITask_TagDelegateTime()
{

    bTickingTask = true;
    started = false;
}

UHITask_TagDelegateTime* UHITask_TagDelegateTime::HITagCustomTickDelegate(UGameplayAbility* OwningAbility, FGameplayTag _tagcheck, float _frequency)
{
    UHITask_TagDelegateTime* myObj = NewAbilityTask<UHITask_TagDelegateTime>(OwningAbility);
    myObj->delegateCallFrecuency = _frequency;
    myObj->tagcheck = _tagcheck;
    return myObj;
}

void UHITask_TagDelegateTime::Activate()
{
    if (!tagcheck.IsValid())
    {
        EndTask();
    }
}

void UHITask_TagDelegateTime::TickTask(float DeltaTime)
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
            delegateFrecuencyElapsed += DeltaTime;
            if (delegateFrecuencyElapsed > delegateCallFrecuency)
            {
                delegateFrecuencyElapsed -= delegateCallFrecuency;
                Tick.Broadcast(DeltaTime);
            }
        }
    }

}

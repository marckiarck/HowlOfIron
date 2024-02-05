// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "HITask_TagDelegateTime.generated.h"

/**
 *
 */




DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCustomTagDelegate, float, elapsedTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartCustomTagDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndCustomTagDelegate);



UCLASS()
class HOWLOFIRON_API UHITask_TagDelegateTime : public UAbilityTask
{
    GENERATED_BODY()


public:

    UHITask_TagDelegateTime();

public:

    UPROPERTY(EditAnywhere)
        FGameplayTag tagcheck;

protected:

private:
    UPROPERTY(BlueprintAssignable)
        FCustomTagDelegate Tick;


    UPROPERTY(BlueprintAssignable)
        FStartCustomTagDelegate AddedTag;


    UPROPERTY(BlueprintAssignable)
        FEndCustomTagDelegate RemovedTag;


    float delegateCallFrecuency;
    float delegateFrecuencyElapsed;

    bool started;
public:


    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
        static UHITask_TagDelegateTime* HITagCustomTickDelegate(UGameplayAbility* OwningAbility, FGameplayTag _tagcheck,float _frequency);

protected:

private:

    virtual void Activate() override;
    virtual void TickTask(float DeltaTime) override;
};

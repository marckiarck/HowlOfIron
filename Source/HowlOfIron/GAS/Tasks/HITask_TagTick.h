// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "HITask_TagTick.generated.h"

/**
 *
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTickTagDelegate, float, elapsedTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartTagDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndTagDelegate);

UCLASS()
class HOWLOFIRON_API UHITask_TagTick : public UAbilityTask
{
    GENERATED_BODY()


public:

    UHITask_TagTick();

public:


    UPROPERTY(EditAnywhere)
        FGameplayTag tagcheck;



protected:

private:

    bool started;

    UPROPERTY(BlueprintAssignable)
        FTickTagDelegate Tick;


    UPROPERTY(BlueprintAssignable)
        FStartTagDelegate AddedTag;


    UPROPERTY(BlueprintAssignable)
        FEndTagDelegate RemovedTag;
public:


    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
        static UHITask_TagTick* HITagTickDelegate(UGameplayAbility* OwningAbility, FGameplayTag _tagcheck);

protected:

private:
    virtual void Activate() override;
    virtual void TickTask(float DeltaTime) override;

};

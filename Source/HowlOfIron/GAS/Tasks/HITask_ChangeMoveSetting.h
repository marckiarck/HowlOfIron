// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "HITask_ChangeMoveSetting.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHITask_ChangeMoveSetting : public UAbilityTask
{
    GENERATED_BODY()


public:
    UHITask_ChangeMoveSetting();

private:
    bool setting;


public:

    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
    static UHITask_ChangeMoveSetting* HIChangeMoveSetting(UGameplayAbility* OwningAbility, bool _setting);

    private:

        virtual void Activate() override;
};

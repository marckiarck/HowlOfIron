// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "HITask_SetRotationToActor.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHITask_SetRotationToActor : public UAbilityTask
{
    GENERATED_BODY()


public:
    UHITask_SetRotationToActor();

private:
   AActor* actorToRotate;


public:

    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
    static UHITask_SetRotationToActor* HISetRotationToActor(UGameplayAbility* OwningAbility,AActor* _actorToRotate);

    private:

        virtual void Activate() override;
};

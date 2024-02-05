// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "UObject/ObjectMacros.h"
#include "HITask_CubeArray.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCubeArrayDelegate, const TArray<AActor*>&, ActorsArray, const TArray<FHitResult>&, HitResutlsArray);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCubeEndDelegate);

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHITask_CubeArray : public UAbilityTask
{
    GENERATED_BODY()

public:
    UHITask_CubeArray();

public:

    UPROPERTY(BlueprintAssignable)
        FCubeArrayDelegate hit;
    UPROPERTY(BlueprintAssignable)
        FCubeEndDelegate noHit;

protected:

private:

    FVector pos;
    FVector size;
    bool drawDebug;

public:

    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
        static UHITask_CubeArray* HICreateCube(UGameplayAbility* OwningAbility, FVector _size, FVector _pos, bool _drawDebug);

protected:

private:

    virtual void Activate() override;
    void HICollideCube();

};

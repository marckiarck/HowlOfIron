// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "UObject/ObjectMacros.h"
#include "HITask_SphereRadius.generated.h"

/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FArrayDelegate, const TArray<AActor*>&, ActorsArray, const TArray<FHitResult>&, HitResutlsArray);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndDelegate);

UCLASS()
class HOWLOFIRON_API UHITask_SphereRadius : public UAbilityTask
{
    GENERATED_BODY()


public:
    UHITask_SphereRadius();

public:
    UPROPERTY(BlueprintAssignable)
        FArrayDelegate hit;
    UPROPERTY(BlueprintAssignable)
        FEndDelegate noHit;

protected:

private:


    FVector pos;
    float radius;
    ECollisionChannel collisionChannel;
    bool drawSphere;

public:

    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
        static UHITask_SphereRadius* HICreateSphere(UGameplayAbility* OwningAbility, float _radius, FVector _pos, ECollisionChannel _collisionChannel, bool _drawDebug);

protected:

private:



    virtual void Activate() override;
    void CollideSphere();

};

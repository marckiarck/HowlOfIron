// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "HITask_CheckInCone.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInConeCheck, const TArray<AHIAbilityCharacter*>&, HIAbilityCharactersInCone);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOffConeCheck);


UCLASS()
class HOWLOFIRON_API UHITask_CheckInCone : public UAbilityTask
{
    GENERATED_BODY()

public:

    UHITask_CheckInCone();
public:

    UPROPERTY(BlueprintAssignable)
        FInConeCheck onHit;

    UPROPERTY(BlueprintAssignable)
        FOffConeCheck noHit;

protected:

private:

    TArray<AHIAbilityCharacter*> abilityCharactersToCheck;
    TArray<AHIAbilityCharacter*> abilityCharactersInCone;

    float lenght;
    float coneAngle;
    FVector emitterPos;
    FVector coneDirection;

public:

    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
        static UHITask_CheckInCone* HICheckInCone(UGameplayAbility* OwningAbility, TArray<AHIAbilityCharacter*>_charactersToCheck, float _lenght, float _coneAngle, FVector _emitterPos, FVector _coneDirection);

protected:

private:

    virtual void Activate() override;

};

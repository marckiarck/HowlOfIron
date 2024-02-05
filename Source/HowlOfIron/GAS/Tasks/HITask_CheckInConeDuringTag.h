// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

 #include "CoreMinimal.h"

#include "Abilities/Tasks/AbilityTask_WaitGameplayTag.h"
#include "Characters/HIAbilityCharacter.h"
 #include "HITask_CheckInConeDuringTag.generated.h"
 
 
  DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInConeCheckDuringTag,  const TArray<AHIAbilityCharacter*>&, HIAbilityCharactersInCone);
  DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOffConeCheckDuringTag);
 
 /**
  * 
  */
 UCLASS()
 class HOWLOFIRON_API UHITask_CheckInConeDuringTag : public UAbilityTask_WaitGameplayTagRemoved
 {
 	GENERATED_BODY()
 	
 
 
 public:
 	UHITask_CheckInConeDuringTag();
 public:
 
     UPROPERTY(BlueprintAssignable)
         FInConeCheckDuringTag onHit;
 
     UPROPERTY(BlueprintAssignable)
         FOffConeCheckDuringTag noHit;
 
 protected:
 
 private:
 
     TArray<AHIAbilityCharacter*> abilityCharactersToCheck;
     TArray<AHIAbilityCharacter*> abilityCharactersInCone;

     float lenght;
     float coneAngle;
     FVector emitterPos;
     FVector coneDirection;
     TSubclassOf<UGameplayEffect> damageGameplayEffect;
  /*   TSubclassOf<UGameplayEffect> removeDamageGameplayEffect;*/
     TSubclassOf<UGameplayEffect> dotAddGameplayEffect;
     TSubclassOf<UGameplayEffect> dotRemoveGameplayEffect;
 
 public:
 
 
     UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
         static UHITask_CheckInConeDuringTag* HICheckInConeDuringTag(UGameplayAbility* OwningAbility,TArray<AHIAbilityCharacter*>_charactersToCheck, float _lenght, float _coneAngle, FVector _emitterPos, FVector _coneDirection, TSubclassOf<UGameplayEffect> _damageGameplayEffect, /*TSubclassOf<UGameplayEffect> _removeDamageGameplayEffect,*/ TSubclassOf<UGameplayEffect> _dotAddGameplayEffect, TSubclassOf<UGameplayEffect> _dotRemoveGameplayEffect, FGameplayTag _removedTag);
 protected:
 
 private:
 
 	virtual void Activate() override;
    virtual void TickTask(float DeltaTime) override;
//     UFUNCTION()
//      void EndTaskGamepplayEffect();


       // virtual void GameplayTagCallback(const FGameplayTag _Tag, int32 NewCount) override;
 };

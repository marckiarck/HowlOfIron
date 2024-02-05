// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

// @Author: Marco Fernandez Garcia

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Abilities/Tasks/AbilityTask.h"
#include <Curves/CurveFloat.h>
#include <Components/TimelineComponent.h>
#include <AlphaBlend.h>
#include "HITask_Dash.generated.h"

/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActivateDash);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FObstacledDash);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndDash);

class ACharacter;

UCLASS()
class HOWLOFIRON_API UHITask_Dash : public UAbilityTask
{
    GENERATED_BODY()

public:
    UHITask_Dash();
    ~UHITask_Dash() { UE_LOG(LogTemp, Log, TEXT("Dash task deleted.")); }

public:
    UPROPERTY(BlueprintAssignable)
        FActivateDash OnActive;
	UPROPERTY(BlueprintAssignable)
        FObstacledDash OnObstacled;
    UPROPERTY(BlueprintAssignable)
        FEndDash OnEnd;

protected:

private:
    float force;
    float dashCorrection;
    float time;
    bool obstacled;



    FVector forwardVector;
    FVector targetDash;
    FVector dashDirection;
    FVector initVector;
    ACharacter* owner;

    AActor* minActor = nullptr;

    FAlphaBlend climbingBlend;

public:
    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
        /// <summary>
        /// Crea la Task y le iguala los valores de argumento a los de la clase
        /// </summary>
        /// <param name="OwningAbility"></param>
        /// <param name="_DashDistance"></param>
        /// <param name="_time"></param>
        /// <param name="_dashCorrection">wide box for redirect direction to an enemy</param>
        /// <returns></returns>
        static UHITask_Dash* HIDash(UGameplayAbility* OwningAbility, float _DashDistance, float _time, float _dashCorrection);

protected:

private:

    /// <summary>
    /// First take a FVector in the player to take the LeftStick to know the direction of the dash and rotate the player to the direction 
    ///if 0 will use forward vector of the player
    /// create a box ahead the player for check if is an enemy inside, if there are more than 1 enemy the dash correction
    /// will choose the enemy near to the forward vector of the player
    /// then will check if the target enemy is on screen, if false  will use the forward vector for the dash 
    /// </summary>
    virtual void Activate() override;

    /// <summary>
    /// will add the direction vector to the target enemy, if no enemy target, will use the forward vector * force, and will check if the floor below
    /// is flat, to change the direction dash for a direction parallel to the floor.
    /// </summary>
    /// <param name="DeltaTime"></param>
    virtual void TickTask(float DeltaTime) override;

};
// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

// @Author: Marco Fernandez Garcia

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include <AlphaBlend.h>
#include "Abilities/Tasks/AbilityTask.h"
#include "HITask_ApproachMove.generated.h"

/**
 *
 */



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActivateApproach, AHIEnemy*, enemyReach);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndApproach);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFailApproach);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOutsideDistance);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReachEnemy);


UCLASS()
class HOWLOFIRON_API UHITask_ApproachMove : public UAbilityTask
{
	GENERATED_BODY()


public:
	UHITask_ApproachMove();
	~UHITask_ApproachMove();

public:

	UPROPERTY(BlueprintAssignable)
		FActivateApproach OnActive;

	UPROPERTY(BlueprintAssignable)
		FEndApproach OnEnd;

	UPROPERTY(BlueprintAssignable)
		FFailApproach OnFail;

	UPROPERTY(BlueprintAssignable)
		FOutsideDistance OnOutside;

	UPROPERTY(BlueprintAssignable)
		FReachEnemy OnReach;



protected:

private:

	class AHIWerewolf* owner = nullptr;

	float circleRadius;

	bool reachedEnemy=false;
	float lessDistance = 9999.f;
	AActor* hitted = nullptr;
	float interpAlpha = 0;
	float interpolationSpeed = 0.1f;
	float wolfEnemySeparation = 0;
	float distanceToDash = 150.f;
	FVector currentPos;
	FVector posBeforeAttack;
	FVector enemyPosBeforeAttack;

	FRotator currentRot;
	FRotator rotBeforeAttack;

	FVector directionHit;
	UCurveFloat* lerpCurve;



	FRotator rotOwner;
	FRotator rotTarget;
	FRotator rotIdeal;



	FAlphaBlend approachBlend;

public:


	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		/// <summary>
		/// Crea la Task y le iguala los valores de argumento a los de la clase
		/// </summary>
		/// <param name="OwningAbility"></param>
		/// <param name="_forwardSize">Largo del cubo generado para comprobar colision</param>
		/// <param name="_SideSize">Ancho del cubo generado para comprobar colision</param>
		/// <param name="_time">Tiempo que tarda en hacer el acercamiento</param>
		/// <returns></returns>
		static UHITask_ApproachMove* HIApproachMovement(UGameplayAbility* OwningAbility, UCurveFloat* _lerpCurve, float _circleRadius, float _interpSpeed,
			float _finalSeparationFromEnemy, float _distanceToIncludeDash);



protected:

private:

	/// <summary>
	/// Create a cube with the members of the class, check if there is an enemy inside. if inside the cube are more than 1 enemy choose the near enemy to the player.
	/// Take the vector direction to the enemy/time to adjust the move to the necesary time
	/// Also set the diference FRotator/time for every tick add the needed Rotation
	/// </summary>
	virtual void Activate() override;

	/// <summary>
	/// Add Actor World location offset and rotation to set the player near the enemy and looking for it.
	/// When the FAlphaBlend end the task end.
	/// </summary>
	/// <param name="DeltaTime"></param>
	virtual void TickTask(float DeltaTime) override;
};

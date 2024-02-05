// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTask.h"
#include "AlphaBlend.h"
#include "Components/SplineComponent.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "HITask_MoveActorbyAlphaBlend.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndMoveToByAlphaBlend);

UCLASS()
class HOWLOFIRON_API UHITask_MoveActorbyAlphaBlend : public UAbilityTask
{
	GENERATED_BODY()

public:
	UHITask_MoveActorbyAlphaBlend();

private:
	FVector startPosition;
	FVector endPosition;
	float moveDuration;
	AActor* actorToMove;
	EAlphaBlendOption interpolationMode;

	FAlphaBlend moveToBlend;
	UPROPERTY(Transient)
	USplineComponent* moveSpline;

	UPROPERTY(BlueprintAssignable)
		FEndMoveToByAlphaBlend onEnd;

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UHITask_MoveActorbyAlphaBlend* HIParabolicMoveActor(UGameplayAbility* OwningAbility, AActor* _actorToMove, FVector _endPosiiton, float _moveDuration, EAlphaBlendOption _interpolationMode);

private:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	void HICreateSpline();
};

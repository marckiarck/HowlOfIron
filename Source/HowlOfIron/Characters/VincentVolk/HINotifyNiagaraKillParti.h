// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifyState_TimedNiagaraEffect.h"
#include "GameplayTagContainer.h"
#include "HINotifyNiagaraKillParti.generated.h"

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class HOWLOFIRON_API UHINotifyNiagaraKillParti : public UAnimNotifyState_TimedNiagaraEffect
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, Category = NiagaraSystem)
		FGameplayTag tagToDestroyNotify;

public:

	void NotifyEnd(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation) override;

};

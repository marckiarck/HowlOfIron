// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/AnimNotifies/HICancelComboAnimNotifyState.h"
#include "HIOnHitCancelComboNotifyState.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHIOnHitCancelComboNotifyState : public UHICancelComboAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
};

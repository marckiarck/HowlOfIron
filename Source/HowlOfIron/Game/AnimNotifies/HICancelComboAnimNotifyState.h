// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Animation/AnimNotifies/AnimNotifyState.h>
#include "HICancelComboAnimNotifyState.generated.h"


UCLASS()
class HOWLOFIRON_API UHICancelComboAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	UPROPERTY(Transient)
	class UAbilitySystemComponent* abilitySystem = nullptr;

public:
	void HICancelCombo(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
};

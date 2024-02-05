// Fill out your copyright notice in the Description page of Project Settings.


#include "HIOnHitCancelComboNotifyState.h"

void UHIOnHitCancelComboNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	bool ownerHitted = false;
	if (abilitySystem)
	{
		CHECK_HAS_TAG(abilitySystem, HIT_TAG, ownerHitted);

		if (ownerHitted)
		{
			Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
		}
	}
	
}

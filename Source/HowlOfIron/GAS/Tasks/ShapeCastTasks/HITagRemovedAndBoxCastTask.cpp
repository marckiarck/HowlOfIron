// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/ShapeCastTasks/HITagRemovedAndBoxCastTask.h"

UHITagRemovedAndBoxCastTask::UHITagRemovedAndBoxCastTask()
{
	bTickingTask = true;
}

UHITagRemovedAndBoxCastTask* UHITagRemovedAndBoxCastTask::HICreateBoxAndWaitTagRemoved(UGameplayAbility* OwningAbility, FVector BoxHalfSize, FVector _pos, FGameplayTag removedTag)
{
	UHITagRemovedAndBoxCastTask* MyObj = NewAbilityTask<UHITagRemovedAndBoxCastTask>(OwningAbility);
	MyObj->Tag = removedTag;
	MyObj->pos = _pos;
	MyObj->boxSize = BoxHalfSize;
	return MyObj;
}

void UHITagRemovedAndBoxCastTask::TickTask(float DeltaTime)
{
	FHitResult hitResult;
	AActor* HitActor;
	FCollisionQueryParams params;
	params.bTraceComplex = true;
	if (GetWorld()->SweepSingleByChannel(hitResult, pos, pos + 0.01f, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeBox(boxSize),params))
	{

		HitActor = hitResult.GetActor();
		UAbilitySystemComponent* hittedAbilitySystem = Cast<IAbilitySystemInterface>(HitActor)->GetAbilitySystemComponent();
		if (hittedAbilitySystem)
		{
			bool inDodge = false;
			CHECK_HAS_TAG(hittedAbilitySystem, DODGE_TAG, inDodge);
			if (inDodge == false)
			{
				OnActive.Broadcast(hitResult);
				DrawDebugBox(GetWorld(), pos, boxSize, FQuat::Identity, HIT_COLOR, false, 0.1f);
				return;
			}
		}
		else
		{
			OnActive.Broadcast(hitResult);
			DrawDebugBox(GetWorld(), pos, boxSize, FQuat::Identity, HIT_COLOR, false, 0.1f);
			return;
		}

		
		DrawDebugBox(GetWorld(), pos, boxSize, FQuat::Identity, NO_HIT_COLOR, false, 0.1f);
	}
	else {
		DrawDebugBox(GetWorld(), pos, boxSize, FQuat::Identity, FColor::Green, false, 0.1f);
	}
}

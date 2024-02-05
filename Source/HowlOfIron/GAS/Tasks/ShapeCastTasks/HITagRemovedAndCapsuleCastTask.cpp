// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/ShapeCastTasks/HITagRemovedAndCapsuleCastTask.h"
#include <DrawDebugHelpers.h>

UHITagRemovedAndCapsuleCastTask::UHITagRemovedAndCapsuleCastTask()
{
	bTickingTask = true;
}

UHITagRemovedAndCapsuleCastTask* UHITagRemovedAndCapsuleCastTask::HICreateCapsuleAndWaitTagRemoved(UGameplayAbility* OwningAbility, float CapsuleRadius, float CapsuleHalfHeight, FVector _pos, FGameplayTag removedTag)
{
	UHITagRemovedAndCapsuleCastTask* MyObj = NewAbilityTask<UHITagRemovedAndCapsuleCastTask>(OwningAbility);
	MyObj->Tag = removedTag;
	MyObj->pos = _pos;
	MyObj->CapsuleRadius = CapsuleRadius;
	MyObj->CapsuleHalfHeight = CapsuleHalfHeight;
	return MyObj;
}

void UHITagRemovedAndCapsuleCastTask::TickTask(float DeltaTime)
{
	FHitResult hitResult;
	AActor* HitActor;

	if (GetWorld()->SweepSingleByChannel(hitResult, pos, pos, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight)))
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
				DrawDebugCapsule(GetWorld(), pos, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, FColor::Red, false, 0.1f);
				return;
			}
		}
		else
		{
			OnActive.Broadcast(hitResult);
			DrawDebugCapsule(GetWorld(), pos, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, FColor::Red, false, 0.1f);
			return;
		}

		DrawDebugCapsule(GetWorld(), pos, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, FColor::Green, false, 0.1f);
	}
	else {
		DrawDebugCapsule(GetWorld(), pos, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, FColor::Green, false, 0.1f);
	}

}

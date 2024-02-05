// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/ShapeCastTasks/HITagRemovedAndSphereCastTask.h"
#include <AbilitySystemInterface.h>

UHITagRemovedAndSphereCastTask::UHITagRemovedAndSphereCastTask()
{
	bTickingTask = true;
}

UHITagRemovedAndSphereCastTask* UHITagRemovedAndSphereCastTask::HICreateSphereAndWaitTagRemoved(UGameplayAbility* OwningAbility, float _radius, FVector _pos, FGameplayTag removedTag)
{
	UHITagRemovedAndSphereCastTask* MyObj = NewAbilityTask<UHITagRemovedAndSphereCastTask>(OwningAbility);
	MyObj->Tag = removedTag;
	MyObj->Pos = _pos;
	MyObj->Radius = _radius;
	return MyObj;
}

void UHITagRemovedAndSphereCastTask::TickTask(float DeltaTime)
{

	FHitResult hitResult;
	AActor* HitActor;

	if (GetWorld()->SweepSingleByChannel(hitResult, Pos, Pos, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius)))
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
				DrawDebugSphere(GetWorld(), Pos, Radius, 16.f, FColor::Red, false, 0.1f);
				return;
			}
		}
		else 
		{
			OnActive.Broadcast(hitResult);
			DrawDebugSphere(GetWorld(), Pos, Radius, 16.f, FColor::Red, false, 0.1f);
			return;
		}

		DrawDebugSphere(GetWorld(), Pos, Radius, 16.f, FColor::Green, false, 0.1f);
		
	}
	else {
		DrawDebugSphere(GetWorld(), Pos, Radius, 16.f, FColor::Green, false, 0.1f);
	}

}
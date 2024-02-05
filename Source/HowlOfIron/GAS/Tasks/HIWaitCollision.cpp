// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HIWaitCollision.h"
#include <Characters/Enemies/HIEnemy.h>

UHIWaitCollision::UHIWaitCollision()
{
	bTickingTask = true;
}

UHIWaitCollision* UHIWaitCollision::HIWaitCollision(UGameplayAbility* OwningAbility)
{
	UHIWaitCollision* returnedTask = NewAbilityTask<UHIWaitCollision>(OwningAbility);

	return returnedTask;
}

void UHIWaitCollision::Activate()
{
	capsuleComponent = Cast<AHIEnemy>(GetAvatarActor())->GetCapsuleComponent();
}

void UHIWaitCollision::TickTask(float DeltaTime)
{
	FHitResult hitResult;
	FCollisionQueryParams params;
	params.AddIgnoredActor(GetAvatarActor());
	if (GetWorld()->SweepSingleByChannel(hitResult, capsuleComponent->GetComponentLocation(), capsuleComponent->GetComponentLocation(), capsuleComponent->GetComponentQuat(), GAME_TRACE_ENEMY, FCollisionShape::MakeCapsule(capsuleComponent->GetScaledCapsuleRadius() + 1.f, capsuleComponent->GetScaledCapsuleHalfHeight() + 0.5f), params))
	{
		OnOwnerHit.Broadcast(hitResult);
		EndTask();
	}
}


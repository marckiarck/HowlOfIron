// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/ShapeCastTasks/HITagRemovedAndSphereCastBySock.h"
#include "Game/HIGameData.h"
#include <Containers/RingBuffer.h>
#include <HIMacros.h>

UHITagRemovedAndSphereCastBySock::UHITagRemovedAndSphereCastBySock()
{
	bTickingTask = true;
}

UHITagRemovedAndSphereCastBySock* UHITagRemovedAndSphereCastBySock::HITagRemovedAndSphereCastBySock(UGameplayAbility* OwningAbility, float assignedSphereRadius, USkeletalMeshComponent* assignedOwnerSkeletalMesh, FName assignedSocketName, FVector assignedPositionOffset, FGameplayTag removedTag)
{
	UHITagRemovedAndSphereCastBySock* MyObj = NewAbilityTask<UHITagRemovedAndSphereCastBySock>(OwningAbility);
	MyObj->Tag = removedTag;
	MyObj->sphereRadius = assignedSphereRadius;
	MyObj->ownerSkeletalMesh = assignedOwnerSkeletalMesh;
	MyObj->socketName = assignedSocketName;
	MyObj->positionOffset = assignedPositionOffset;
	MyObj->hittedActor = nullptr;
	return MyObj;
}

void UHITagRemovedAndSphereCastBySock::TickTask(float DeltaTime)
{
	if (tagRemoved == false)
	{
		HIUpdateCenterPosition();

		FHitResult hitResult;

		if (GetWorld()->SweepSingleByChannel(hitResult, sphereCenter, sphereCenter, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(sphereRadius)))
		{

			if (hittedActors.Contains(hitResult.GetActor()) == false)
			{
				AActor* hitActor = hitResult.GetActor();
				UAbilitySystemComponent* hittedAbilitySystem = Cast<IAbilitySystemInterface>(hitActor)->GetAbilitySystemComponent();

				if (hittedAbilitySystem)
				{
					bool inDodge = false;
					CHECK_HAS_TAG(hittedAbilitySystem, DODGE_TAG, inDodge);
					if (inDodge == false)
					{
						AddHittedActor(hitResult);
						return;
					}
				}
				else
				{
					AddHittedActor(hitResult);
					return;
				}

				if (UHIGameData::HIGetDebugMode())
				{
					DrawDebugSphere(GetWorld(), sphereCenter, sphereRadius, 16.f, FColor::Green, false, 0.1f);
				}
			}
		}
		else
		{
			if (UHIGameData::HIGetDebugMode())
			{
				DrawDebugSphere(GetWorld(), sphereCenter, sphereRadius, 16.f, FColor::Green, false, 0.1f);
			}
		}
	}
}

void UHITagRemovedAndSphereCastBySock::AddHittedActor(FHitResult& hitResult)
{
	if (UHIGameData::HIGetDebugMode())
	{
		DrawDebugSphere(GetWorld(), sphereCenter, sphereRadius, 16.f, FColor::Red, false, 0.1f);
	}

	if (hittedActors.Num() == 0)
	{
		UAbilitySystemComponent* ownerAbilitySystem = Cast<UAbilitySystemComponent>(Cast<IAbilitySystemInterface>(GetAvatarActor())->GetAbilitySystemComponent());
		ownerAbilitySystem->AddLooseGameplayTag(GET_GAMEPLAY_TAG(HIT_TAG));
	}

	hittedActors.Add(hitResult.GetActor());

	FHitResult floorHit;
	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	FVector endLocation = FVector(0.f, 0.f, -400.f);
	GetWorld()->LineTraceSingleByObjectType(floorHit, hitResult.Location, hitResult.Location + endLocation, QueryParams);

	OnHit.Broadcast(hitResult, floorHit);
}

void UHITagRemovedAndSphereCastBySock::GameplayTagCallback(const FGameplayTag RemovedTag, int32 NewCount)
{
	Super::GameplayTagCallback(RemovedTag, NewCount);

	tagRemoved = true;
}

void UHITagRemovedAndSphereCastBySock::OnDestroy(bool bInOwnerFinished)
{
	UAbilitySystemComponent* ownerAbilitySystem = Cast<UAbilitySystemComponent>(Cast<IAbilitySystemInterface>(GetAvatarActor())->GetAbilitySystemComponent());
	ownerAbilitySystem->RemoveLooseGameplayTag(GET_GAMEPLAY_TAG(HIT_TAG));

	Super::OnDestroy(bInOwnerFinished);
}

void UHITagRemovedAndSphereCastBySock::HIUpdateCenterPosition()
{
	if (ownerSkeletalMesh)
	{
		FVector socketLocation = ownerSkeletalMesh->GetSocketLocation(socketName);
		sphereCenter = socketLocation + positionOffset;
	}
	else {
		tagRemoved = true;
	}

}

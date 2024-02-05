// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/ShapeCastTasks/HITagRemovedAndCapsuleCastBySock.h"

UHITagRemovedAndCapsuleCastBySock::UHITagRemovedAndCapsuleCastBySock() : tagRemoved(false)
{
	bTickingTask = true;
}

UHITagRemovedAndCapsuleCastBySock* UHITagRemovedAndCapsuleCastBySock::HITagRemovedAndCapsuleCastBySock(UGameplayAbility* OwningAbility, float assigendCapsuleRadius, float assignedcapsuleHalfHeight, USkeletalMeshComponent* assignedOwnerSkeletalMesh, FName assignedSocketName, FVector assignedPositionOffset, FRotator _rotationOffset, FGameplayTag removedTag)
{
	UHITagRemovedAndCapsuleCastBySock* MyObj = NewAbilityTask<UHITagRemovedAndCapsuleCastBySock>(OwningAbility);
	MyObj->Tag = removedTag;
	MyObj->capsuleRadius = assigendCapsuleRadius;
	MyObj->capsuleHalfHeight = assignedcapsuleHalfHeight;
	MyObj->ownerSkeletalMesh = assignedOwnerSkeletalMesh;
	MyObj->socketName = assignedSocketName;
	MyObj->positionOffset = assignedPositionOffset;
	MyObj->rotationOffset = _rotationOffset;
	MyObj->hittedActor = nullptr;
	return MyObj;
}

void UHITagRemovedAndCapsuleCastBySock::TickTask(float DeltaTime)
{

	FRotator rotatorowner = AbilitySystemComponent->GetAvatarActor()->GetActorRotation();
	FRotator result = rotatorowner + rotationOffset;
	FQuat quatRotation = result.Quaternion();

	if (tagRemoved == false)
	{
		HIUpdateCenterPosition();

		FHitResult hitResult;

		if (GetWorld()->SweepSingleByChannel(hitResult, capsuleCenter, capsuleCenter, quatRotation, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeCapsule(capsuleRadius, capsuleHalfHeight)))
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

						if (UHIGameData::HIGetDebugMode())
						{
							DrawDebugCapsule(GetWorld(), capsuleCenter, capsuleHalfHeight, capsuleRadius, quatRotation, HIT_COLOR, false, 0.1f);
						}
						return;
					}
				}
				else
				{
					AddHittedActor(hitResult);

					if (UHIGameData::HIGetDebugMode())
					{
						DrawDebugCapsule(GetWorld(), capsuleCenter, capsuleHalfHeight, capsuleRadius, quatRotation, HIT_COLOR, false, 0.1f);
					}
					return;
				}

				if (UHIGameData::HIGetDebugMode())
				{
					DrawDebugCapsule(GetWorld(), capsuleCenter, capsuleHalfHeight, capsuleRadius, quatRotation, NO_HIT_COLOR, false, 0.1f);
				}
			}
		}
		else
		{
			if (UHIGameData::HIGetDebugMode())
			{
				DrawDebugCapsule(GetWorld(), capsuleCenter, capsuleHalfHeight, capsuleRadius, quatRotation, NO_HIT_COLOR, false, 0.1f);
			}
		}
	}
}

void UHITagRemovedAndCapsuleCastBySock::OnDestroy(bool bInOwnerFinished)
{
	UAbilitySystemComponent* ownerAbilitySystem = Cast<UAbilitySystemComponent>(Cast<IAbilitySystemInterface>(GetAvatarActor())->GetAbilitySystemComponent());
	ownerAbilitySystem->RemoveLooseGameplayTag(GET_GAMEPLAY_TAG(HIT_TAG));

	Super::OnDestroy(bInOwnerFinished);
}

void UHITagRemovedAndCapsuleCastBySock::GameplayTagCallback(const FGameplayTag RemovedTag, int32 NewCount)
{
	Super::GameplayTagCallback(RemovedTag, NewCount);

	tagRemoved = true;
}

void UHITagRemovedAndCapsuleCastBySock::HIUpdateCenterPosition()
{
	FVector socketLocation = ownerSkeletalMesh->GetSocketLocation(socketName);
	capsuleCenter = socketLocation + positionOffset;
}

void UHITagRemovedAndCapsuleCastBySock::AddHittedActor(FHitResult& hitResult)
{

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

// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AnimNotifies/HISocketSphereCastAnimNotifyState.h"
#include <Engine/SkeletalMeshSocket.h>
#include <Characters/Enemies/HIEnemy.h>
#include <GameplayEffectTypes.h>
#include "HIMacros.h"

void UHISocketSphereCastAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	targetEnemy = nullptr;
}

void UHISocketSphereCastAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	UWorld* affectedWorld = MeshComp->GetWorld();
	FVector socketLocation = MeshComp->GetSocketLocation(socketName);

	if (affectedWorld)
	{
		FHitResult hitResult;
		FVector aparitionPos = socketLocation + positionOffset;

		if (usingSocket == false && MeshComp && MeshComp->GetOwner())
		{
			aparitionPos = socketLocation + MeshComp->GetOwner()->GetActorForwardVector() * shapeDistance;
		}


		switch (shape)
		{
		case typeShapeCast::BOX:
		{

			if (affectedWorld->SweepSingleByChannel(hitResult, aparitionPos, aparitionPos + 0.00001f, FQuat::Identity, GAME_TRACE_ENEMY, FCollisionShape::MakeBox(boxhalfExtended)))
			{
				//DrawDebugBox(affectedWorld, aparitionPos, boxhalfExtended, FQuat::Identity, HIT_COLOR, false, 0.1f);
				AActor* hitedActor = hitResult.GetActor();
				AHIEnemy* hitedEnemy = Cast<AHIEnemy>(hitedActor);
				if (hitedEnemy)
				{
					targetEnemy = hitedEnemy;
				}
			}
			else
			{
				//DrawDebugBox(affectedWorld, aparitionPos, boxhalfExtended, FQuat::Identity, NO_HIT_COLOR, false, 0.1f);
			}
		}
		break;

		case typeShapeCast::SPHERE:
		{
			if (affectedWorld->SweepSingleByChannel(hitResult, aparitionPos, aparitionPos, FQuat::Identity, GAME_TRACE_ENEMY, FCollisionShape::MakeSphere(sphereRadious)))
			{
				
				//DrawDebugSphere(affectedWorld, aparitionPos, sphereRadious, 16.f, HIT_COLOR, false, 0.1f);
				

				AActor* hitedActor = hitResult.GetActor();
				AHIEnemy* hitedEnemy = Cast<AHIEnemy>(hitedActor);

				if (hitedEnemy)
				{
					targetEnemy = hitedEnemy;
				}

			}
			else
			{
				//DrawDebugSphere(affectedWorld, aparitionPos, sphereRadious, 16.f, NO_HIT_COLOR, false, 0.1f);
			}
		}
		break;

		case typeShapeCast::CAPSULE:
		{
			if (affectedWorld->SweepSingleByChannel(hitResult, aparitionPos, aparitionPos, FQuat::Identity, GAME_TRACE_ENEMY, FCollisionShape::MakeCapsule(capsuleRadious,capsuleHeight)))
			{
				
				//DrawDebugCapsule(affectedWorld, aparitionPos, capsuleHeight, capsuleRadious, FQuat::Identity, HIT_COLOR, false, 0.1f);

				AActor* hitedActor = hitResult.GetActor();
				AHIEnemy* hitedEnemy = Cast<AHIEnemy>(hitedActor);

				if (hitedEnemy)
				{
					targetEnemy = hitedEnemy;
				}
			}
			else
			{
				//DrawDebugCapsule(affectedWorld, aparitionPos, capsuleHeight, capsuleRadious, FQuat::Identity, NO_HIT_COLOR, false, 0.1f);
			}
		}
		break;
		}
	}
}

void UHISocketSphereCastAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (targetEnemy)
	{
		if (appliedGameplayEffect) 
		{
			if (targetEnemy) 
			{
				UAbilitySystemComponent* enemyAbilitySystem = targetEnemy->GetAbilitySystemComponent();
				UGameplayEffect* effect = Cast<UGameplayEffect>(appliedGameplayEffect->GetDefaultObject());
				
				enemyAbilitySystem->ApplyGameplayEffectToSelf(effect, 0.f, FGameplayEffectContextHandle());
				effect->ConditionalBeginDestroy();
			}
		}
	}
}

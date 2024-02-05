// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AnimNotifies/HIHitAnimAnimNotifyState.h"
#include <DrawDebugHelpers.h>

void UHIHitAnimAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	UWorld* affectedWorld = MeshComp->GetWorld();
	if (affectedWorld)
	{
		TArray<struct FHitResult> outHits;

		FBoxSphereBounds sphereBounds = MeshComp->CalcBounds(MeshComp->GetRelativeTransform());
		FVector aparitionPos = MeshComp->GetOwner()->GetActorLocation() + FVector(0.f, 0.f, sphereBounds.BoxExtent.Z / 2) + positionOffset;

		affectedWorld->SweepMultiByChannel(outHits, aparitionPos, aparitionPos, FQuat::Identity, ECollisionChannel::ECC_EngineTraceChannel1, FCollisionShape::MakeSphere(sphereRadious));
		DrawDebugSphere(affectedWorld, aparitionPos, sphereRadious, 16.f, FColor::Red, false, 0.1f);

		for (FHitResult hitResult : outHits)
		{
			UE_LOG(LogTemp, Warning, TEXT("TU madre"));
		}
	}
}

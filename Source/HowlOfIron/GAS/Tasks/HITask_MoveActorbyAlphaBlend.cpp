// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HITask_MoveActorbyAlphaBlend.h"
#include <Math/UnrealMathUtility.h>

UHITask_MoveActorbyAlphaBlend::UHITask_MoveActorbyAlphaBlend()
{
	bTickingTask = true;
	moveSpline = CreateDefaultSubobject<USplineComponent>(TEXT("MoveSpline"));
}

UHITask_MoveActorbyAlphaBlend* UHITask_MoveActorbyAlphaBlend::HIParabolicMoveActor(UGameplayAbility* OwningAbility, AActor* _actorToMove, FVector _endPosiiton, float _moveDuration, EAlphaBlendOption _interpolationMode)
{
	UHITask_MoveActorbyAlphaBlend* moveToTask = NewAbilityTask<UHITask_MoveActorbyAlphaBlend>(OwningAbility);
	moveToTask->moveDuration = _moveDuration;
	moveToTask->interpolationMode = _interpolationMode;
	moveToTask->actorToMove = _actorToMove;
	moveToTask->startPosition = _actorToMove->GetActorLocation();
	moveToTask->endPosition = _endPosiiton;

	return moveToTask;
}

void UHITask_MoveActorbyAlphaBlend::Activate()
{
	HICreateSpline();

	moveToBlend.SetBlendOption(interpolationMode);
	moveToBlend.SetBlendTime(moveDuration);
	moveToBlend.Reset();
}

void UHITask_MoveActorbyAlphaBlend::TickTask(float DeltaTime)
{
	moveToBlend.Update(DeltaTime);


	float distance = FMath::Lerp(0.f, moveSpline->GetSplineLength(), moveToBlend.GetAlpha());

	FVector dstLoc = moveSpline->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World);
	bool swept = actorToMove->SetActorLocation(moveSpline->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World), true);

	if (moveToBlend.IsComplete())
	{
		onEnd.Broadcast();
		EndTask();
	}

}

void UHITask_MoveActorbyAlphaBlend::HICreateSpline()
{
	FVector mediumPoint = (startPosition + endPosition) * 0.5f;
	float distanceBetweenZValues = FMath::Abs(startPosition.Z - endPosition.Z);
	float mediumPointZValue = FMath::Max(startPosition.Z, endPosition.Z) + ((distanceBetweenZValues / 10.f) * 2.f) + distanceBetweenZValues;
	mediumPoint.Z = mediumPointZValue;

	moveSpline->ClearSplinePoints();
	moveSpline->AddSplinePoint(startPosition, ESplineCoordinateSpace::World);
	moveSpline->AddSplinePoint(mediumPoint, ESplineCoordinateSpace::World);
	moveSpline->AddSplinePoint(endPosition, ESplineCoordinateSpace::World);
}

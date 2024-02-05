// @AUTHOR: Carlos

#include "HITask_Climb.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UHITask_Climb::UHITask_Climb()
{
	bTickingTask = true;
	climbSpline = CreateDefaultSubobject<USplineComponent>(TEXT("ClimbSpline"));
}

UHITask_Climb* UHITask_Climb::HIClimb(UGameplayAbility* OwningAbility, float _climbingSpeed, float _heightOfWall)
{
	UHITask_Climb* climb = NewAbilityTask<UHITask_Climb>(OwningAbility);

	climb->climbingSpeed = _climbingSpeed;
	climb->heightOfWall = _heightOfWall;

	return climb;
}

void UHITask_Climb::Activate()
{
	AActor* actor = GetAvatarActor();
	owner = Cast<ACharacter>(actor);
	OnActive.Broadcast();

	climbSpline->ClearSplinePoints();
	climbSpline->AddSplinePoint(owner->GetActorLocation(), ESplineCoordinateSpace::World);
	FVector endPosition = owner->GetActorLocation();
	endPosition.Z = heightOfWall;
	climbSpline->AddSplinePoint(endPosition, ESplineCoordinateSpace::World);

	owner->GetCharacterMovement()->Velocity = endPosition - owner->GetActorLocation();
	float climbingTime = climbSpline->GetSplineLength() / climbingSpeed;
	climbingBlend = FAlphaBlend(climbingTime);


}

void UHITask_Climb::TickTask(float DeltaTime)
{
	climbingBlend.Update(DeltaTime);

	if (climbSpline && IsValid(climbSpline) && !climbSpline->IsPendingKill())
	{
		float distance = FMath::Lerp(0.f, climbSpline->GetSplineLength(), climbingBlend.GetAlpha());
		owner->SetActorLocation(climbSpline->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World));

		if (climbingBlend.IsComplete())
		{
			owner->GetCharacterMovement()->Velocity = FVector::ZeroVector;
			OnEnd.Broadcast();
			EndTask();
		}
	}
}
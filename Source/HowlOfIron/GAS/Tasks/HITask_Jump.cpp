// @AUTHOR: Carlos


#include "HITask_Jump.h"
#include "Characters/VincentVolk/HIWerewolf.h"
#include "Components/CapsuleComponent.h"
#include "Components/SplineComponent.h"
#include "Game/HICameraManager.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HIMacros.h"
#include "Kismet/GameplayStatics.h"
#include "MapLogic/HIBuilding.h"
#include "UI/HIButtonHUD.h"

UHITask_Jump::UHITask_Jump()
{
	bTickingTask = true;
	jumpSpline = CreateDefaultSubobject<USplineComponent>(TEXT("JumpSpline"));
}

UHITask_Jump* UHITask_Jump::HIJump(UGameplayAbility* OwningAbility, float _jumpVelocity, TArray<FVector> _splinePoints)
{
	UHITask_Jump* jump = NewAbilityTask<UHITask_Jump>(OwningAbility);

	jump->jumpVelocity = _jumpVelocity;
	jump->splinePoints = _splinePoints;

	return jump;
}

void UHITask_Jump::Activate()
{
	AActor* actor = GetAvatarActor();
	owner = Cast<AHICharacter>(actor);
	OnActive.Broadcast();

	// Rotate the werewolf. @TODO: Do it slowly?
	AHIWerewolf* wolf = Cast<AHIWerewolf>(owner);
	if (wolf)
	{
		FVector forwardVector = wolf->cineCamera->GetForwardVector();
		forwardVector.Z = wolf->GetActorForwardVector().Z;
		wolf->SetActorRotation(forwardVector.Rotation());

		werewolfCollisionEnabled = false;
		wolf->GetCapsuleComponent()->SetCollisionProfileName(COLLISION_JUMPING);
	}

	// Add spline points to jumpSpline
	jumpSpline->ClearSplinePoints();
	for (FVector splinePoint : splinePoints)
	{
		jumpSpline->AddSplinePoint(splinePoint, ESplineCoordinateSpace::World);
	}

	float jumpingTime = jumpSpline->GetSplineLength() / jumpVelocity;
	jumpBlend = FAlphaBlend(jumpingTime);

}

void UHITask_Jump::TickTask(float DeltaTime)
{
	jumpBlend.Update(DeltaTime);

	if (jumpSpline && IsValid(jumpSpline) && !jumpSpline->IsPendingKill())
	{
		float distance = FMath::Lerp(0.f, jumpSpline->GetSplineLength(), jumpBlend.GetAlpha());
		bool swept = owner->SetActorLocation(jumpSpline->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World), true);

		// Change collision profile to allow collisions in the second half of the jump
		if (distance >= jumpSpline->GetSplineLength() * 0.5f && !werewolfCollisionEnabled)
		{
			werewolfCollisionEnabled = true;
			owner->GetCapsuleComponent()->SetCollisionProfileName(COLLISION_WEREWOLF);
		}

		if (!swept || jumpBlend.IsComplete())
		{
			owner->GetCharacterMovement()->Velocity = owner->GetActorForwardVector(); // To collide with a wall if there is one
			OnEnd.Broadcast();
			EndTask();
		}
	}
}
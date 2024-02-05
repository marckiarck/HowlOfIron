// Fill out your copyright notice in the Description page of Project Settings.


#include "HITask_Dash.h"
#include "Characters/VincentVolk/HIWerewolf.h"
#include "DrawDebugHelpers.h"
#include "Game/HIGameData.h"
#include "GameFramework/Character.h"
#include "HIMacros.h"
#include "Kismet/KismetMathLibrary.h"

UHITask_Dash::UHITask_Dash()
{
	bTickingTask = true;
}


UHITask_Dash* UHITask_Dash::HIDash(UGameplayAbility* OwningAbility, float _DashDistance, float _time, float _dashCorrection)
{
	UHITask_Dash* dash = NewAbilityTask<UHITask_Dash>(OwningAbility);
	dash->force = _DashDistance;
	if (_time <= 0.f)
	{
		dash->time = 0.00001f;
	}
	else
	{
		dash->time = _time;
	}
	dash->dashCorrection = _dashCorrection;


	return dash;
}


void UHITask_Dash::Activate()
{
	AActor* actor = GetAvatarActor();
	owner = Cast<ACharacter>(actor);
	AHIWerewolf* player = UHIGameData::HIGetPlayerWerewolf();
	initVector = owner->GetActorLocation();

	bool isRayHit = false;
	FHitResult outHit;
	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActor(owner);

	if (player->resultVectorInput.Size() != 0)
	{
		FVector targetPoint = (player->resultVectorInput * force) + owner->GetActorLocation();
		owner->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(player->GetActorLocation(), targetPoint));

	}
	player->resultVectorInput = FVector::ZeroVector;


	forwardVector = owner->GetActorForwardVector();
	targetDash = (forwardVector * force) + owner->GetActorLocation();


	APlayerController* Controll = owner->GetController<APlayerController>();


	FVector playerLocation = player->GetActorLocation();
	FVector CubePosition = playerLocation + (forwardVector * (2.f * (force / 3.f)));
	FVector cubeShape = FVector(force / 3.f, dashCorrection, 300.f);

	TArray<FHitResult> hitResults;

	float mindot = 0.f;

	if (GetWorld()->SweepMultiByChannel(hitResults, CubePosition, CubePosition + 0.00001f, forwardVector.ToOrientationQuat() /*player->GetActorQuat()*/, GAME_TRACE_ENEMY, FCollisionShape::MakeBox(cubeShape)))
	{
		if (UHIGameData::HIGetDebugMode())
		{
			DrawDebugBox(GetWorld(), CubePosition, cubeShape, forwardVector.ToOrientationQuat()/*player->GetActorQuat()*/, FColor::Red, false, 5.f);
			DrawDebugLine(GetWorld(), playerLocation, playerLocation + (forwardVector * force), FColor::Red, false, 5.f);
		}

		for (FHitResult hit : hitResults)
		{
			float tempdot = 0;

			FVector tempdotvector = hit.Actor->GetActorLocation() - player->GetActorLocation();

			tempdotvector = tempdotvector.GetSafeNormal();

			tempdot = FVector::DotProduct(player->GetActorForwardVector(), tempdotvector);

			if (tempdot >= mindot)
			{
				minActor = hit.GetActor();
				mindot = tempdot;
			}
		}
	}
	else
	{
		if (UHIGameData::HIGetDebugMode())
		{
			DrawDebugBox(GetWorld(), CubePosition, cubeShape, forwardVector.ToOrientationQuat() /*player->GetActorQuat()*/, FColor::Green, false, 5.f);
			DrawDebugLine(GetWorld(), playerLocation, playerLocation + (forwardVector * force), FColor::Green, false, 5.f);
		}
	}

	if (minActor)
	{
		if (UHIGameData::HIIsPositionOnScreen(minActor->GetActorLocation()))
		{
			targetDash = minActor->GetActorLocation();
		}
	}

	dashDirection = targetDash - owner->GetActorLocation();
	dashDirection.Normalize(0.00001);


	isRayHit = GetWorld()->LineTraceSingleByChannel(outHit, FVector(playerLocation.X, playerLocation.Y, playerLocation.Z - 20.f), FVector(playerLocation.X, playerLocation.Y, playerLocation.Z - 20.f) + dashDirection * force, ECC_Visibility, collisionParams);

	if (isRayHit)
	{
		float force2 = UKismetMathLibrary::Vector_Distance(playerLocation, outHit.Location);
		float time2 = time * force2 / force;

		if (UHIGameData::HIGetDebugMode())
		{
			DrawDebugLine(GetWorld(), FVector(playerLocation.X, playerLocation.Y, playerLocation.Z - 20.f), outHit.Location, FColor::Purple, false, 5.f, 0.f, 15.f);
		}

		force = force2;
		time = time2;
		obstacled = true;
	}

	climbingBlend.SetBlendOption(EAlphaBlendOption::Linear);
	climbingBlend.SetBlendTime(time);
	climbingBlend.Reset();

	OnActive.Broadcast();
}

void UHITask_Dash::TickTask(float DeltaTime)
{
	climbingBlend.Update(DeltaTime);

	if (minActor)
	{
		owner->AddActorWorldOffset((dashDirection * (force / time)) * DeltaTime, true);
	}
	else
	{
		FHitResult ground;
		FVector tracedown = FVector(0.f, 0.f, -500.f);
		FCollisionObjectQueryParams QueryParams;
		QueryParams.AddObjectTypesToQuery(ECC_WorldStatic);

		GetWorld()->LineTraceSingleByObjectType(ground, owner->GetActorLocation(), owner->GetActorLocation() + tracedown, QueryParams);


		FVector slopeNormal = ground.Normal;
		FVector leftVector = owner->GetActorRightVector();
		leftVector = leftVector * -1.f;

		dashDirection = FVector::CrossProduct(slopeNormal, leftVector);

		owner->AddActorWorldOffset((dashDirection * (force / time)) * DeltaTime, true);
	}


	if (climbingBlend.IsComplete())
	{
		if (!obstacled)
		{
			OnEnd.Broadcast();
		}
		else
		{
			OnObstacled.Broadcast();
		}
		EndTask();
		return;
	}

	return;

}


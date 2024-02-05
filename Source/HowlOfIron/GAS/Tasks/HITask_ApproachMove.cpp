// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HITask_ApproachMove.h"
#include "Characters/Enemies/HIEnemy.h"
#include "Characters/VincentVolk/HIWerewolf.h"
#include "Characters/VincentVolk/HIWerewolfController.h"
#include "DrawDebugHelpers.h"
#include "Game/HICameraManager.h"
#include "Game/HIGameData.h"
#include "DrawDebugHelpers.h"
#include "HIMacros.h"
#include "Kismet/KismetMathLibrary.h"
#include <Math/UnrealMathUtility.h>


UHITask_ApproachMove::UHITask_ApproachMove()
{
	bTickingTask = true;
}

UHITask_ApproachMove::~UHITask_ApproachMove()
{

}

UHITask_ApproachMove* UHITask_ApproachMove::HIApproachMovement(UGameplayAbility* OwningAbility, UCurveFloat* _lerpCurve, float _circleRadius,
	float _interpSpeed, float _finalSeparationFromEnemy, float _distanceToIncludeDash)
{
	UHITask_ApproachMove* myObj = NewAbilityTask<UHITask_ApproachMove>(OwningAbility);
	myObj->circleRadius = _circleRadius;
	myObj->lerpCurve = _lerpCurve;
	myObj->interpolationSpeed = _interpSpeed;
	myObj->wolfEnemySeparation = _finalSeparationFromEnemy;
	myObj->distanceToDash = _distanceToIncludeDash;
	float rad = _circleRadius;
	return myObj;
}

void UHITask_ApproachMove::Activate()
{

	owner = Cast<AHIWerewolf>(GetAvatarActor());

	float lessDistanceAttack = 9999.f;
	FVector playerLocation = owner->GetActorLocation();
	FVector circlePosition = playerLocation;
	FVector direction = FVector(0.f, 0.f, 0.f);
	FVector directionEnem = FVector(0.f, 0.f, 0.f);
	TArray<FHitResult> hitResults;
	FHitResult outHit;
	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActor(owner);
	float dis = 0;
	float mindis = 0;
	float dir;
	float dirEne;
	FVector dirCam;
	bool isRayHit = false;

	AHIWerewolfController* contr = Cast<AHIWerewolfController>(owner->GetController());

	hitted = nullptr;

	if (owner->camManager->targetedActor)
	{
		if (owner->GetDistanceTo(owner->camManager->targetedActor) < circleRadius)
		{
			hitted = owner->camManager->targetedActor;
			lessDistanceAttack = owner->GetDistanceTo(owner->camManager->targetedActor);
		}
	}
	else
	{
		if (GetWorld()->SweepMultiByChannel(hitResults, circlePosition, circlePosition + 0.000001f, owner->GetActorQuat(), GAME_TRACE_ENEMY, FCollisionShape::MakeSphere(circleRadius)))
		{
			FVector wolfLoc = owner->GetActorLocation();
			FVector enemLoc;

			for (size_t i = 0; i < hitResults.Num(); ++i)
			{
				enemLoc = hitResults[i].GetActor()->GetActorLocation();

				//if you are inputing in a direction, attacks to an enemy there, the enemy has to be also the closest, in camera view and at same height
				if (contr->movementImput.Size() > 0.2f)
				{
					dirEne = (hitResults[i].GetActor()->GetActorLocation() - wolfLoc).Rotation().Yaw;
					dirCam = wolfLoc - owner->cineCamera->GetComponentLocation();
					dir = (dirCam.Rotation() + contr->movementImput.Rotation()).Yaw;

					float Ang;

					if (dir >= dirEne)
					{
						Ang = dir - dirEne;
					}
					else
					{
						Ang = dirEne - dir;
					}

					/*if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Emerald, FString::SanitizeFloat(dirEne));
						GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Green, FString::SanitizeFloat(dir));
						GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, FString::SanitizeFloat(Ang));
					}*/

					for (size_t j = 1; j < 30; ++j)
					{
						//GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, FString::SanitizeFloat(12.f*j));

						if (Ang < 3.f * j || Ang>360 - 3.f * j)
						{
							dis = owner->GetDistanceTo(hitResults[i].GetActor());

							if (mindis == 0 || dis < mindis)
							{
								if (UHIGameData::HIIsPositionOnScreen(enemLoc))
								{
									if (FMath::Abs(wolfLoc.Z - enemLoc.Z) < 50.f)
									{
										isRayHit = GetWorld()->LineTraceSingleByChannel(outHit, FVector(wolfLoc.X, wolfLoc.Y, wolfLoc.Z - 20.f), FVector(enemLoc.X, enemLoc.Y, enemLoc.Z - 20.f), ECC_Visibility, collisionParams);

										if (isRayHit)
										{
											AHIEnemy* enem = Cast<AHIEnemy>(outHit.GetActor());

											if (enem)
											{
												hitted = hitResults[i].GetActor();
												lessDistanceAttack = owner->GetDistanceTo(hitted);
												mindis = dis;
												break;
											}
										}
									}
								}
							}
						}
					}

				}
				else
				{
					dis = owner->GetDistanceTo(hitResults[i].GetActor());

					if (mindis == 0 || dis < mindis)
					{
						if (UHIGameData::HIIsPositionOnScreen(hitResults[i].GetActor()->GetActorLocation()))
						{

							if (FMath::Abs(wolfLoc.Z - enemLoc.Z) < 50.f)
							{
								isRayHit = GetWorld()->LineTraceSingleByChannel(outHit, FVector(wolfLoc.X, wolfLoc.Y, wolfLoc.Z - 20.f), FVector(enemLoc.X, enemLoc.Y, enemLoc.Z - 20.f), ECC_Visibility, collisionParams);

								if (isRayHit)
								{
									AHIEnemy* enem = Cast<AHIEnemy>(outHit.GetActor());

									if (enem)
									{
										hitted = hitResults[i].GetActor();
										lessDistanceAttack = owner->GetDistanceTo(hitted);
										mindis = dis;
									}
								}
							}
						}
					}
				}
			}


			if (UHIGameData::HIGetDebugMode())
			{
				DrawDebugSphere(GetWorld(), circlePosition, circleRadius, 16.f, FColor::Red, false, 2.f);
			}
		}
		else if (UHIGameData::HIGetDebugMode())
		{
			DrawDebugSphere(GetWorld(), circlePosition, circleRadius, 16.f, FColor::Green, false, 2.f);
		}
	}

	if (hitted)
	{
		AHIEnemy* enem = Cast<AHIEnemy>(hitted);
		
// 		UGameplayEffect* effect = Cast<UGameplayEffect>(enem->stopWhenAttackedEffect->GetDefaultObject());
// 		enem->GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(effect, 0.f, FGameplayEffectContextHandle());
// 		effect->ConditionalBeginDestroy();

		directionHit = hitted->GetActorLocation() - owner->GetActorLocation();
		posBeforeAttack = owner->GetActorLocation();

		//enemyPosBeforeAttack = hitted->GetActorLocation() - UKismetMathLibrary::GetDirectionUnitVector(owner->GetActorLocation(), hitted->GetActorLocation()) * wolfEnemySeparation;

		rotBeforeAttack = owner->GetActorRotation();
		directionHit.Normalize(0.00001f);

		lessDistance = lessDistanceAttack;

		OnActive.Broadcast(enem);

		rotOwner = owner->GetActorRotation();
		rotTarget = UKismetMathLibrary::FindLookAtRotation(owner->GetActorLocation(), hitted->GetActorLocation());

		rotIdeal = rotTarget;
		rotIdeal.Pitch = 0;
		rotIdeal.Roll = 0;
		rotIdeal.Normalize();

		AHIWerewolf* wolfito = UHIGameData::HIGetPlayerWerewolf();
		wolfito->camManager->targetSnapped = hitted;

		if (UHIGameData::HIGetDebugMode())
		{
			DrawDebugLine(GetWorld(), posBeforeAttack, enemyPosBeforeAttack, FColor(255, 0, 0), false, 1, 0, 2);
			DrawDebugSphere(GetWorld(), enemyPosBeforeAttack, 10, 8, FColor(0, 255, 0), false, 1, -1, 10);

			DrawDebugLine(GetWorld(), hitted->GetActorLocation(), enemyPosBeforeAttack, FColor(0, 122, 122), false, 1, 0, 3);
			DrawDebugSphere(GetWorld(), hitted->GetActorLocation(), 10, 8, FColor(0, 0, 255), false, 1, -1, 10);

			DrawDebugSphere(GetWorld(), posBeforeAttack, 10, 8, FColor(122, 0, 122), false, 1, -1, 10);
		}

		if (UKismetMathLibrary::Vector_Distance(owner->GetActorLocation(), hitted->GetActorLocation()) < distanceToDash)
		{
			OnReach.Broadcast();
			reachedEnemy = true;
		}
		else
		{
			OnOutside.Broadcast();
			reachedEnemy = false;
		}
	}
	else
	{
		OnFail.Broadcast();
		EndTask();
	}
}

void UHITask_ApproachMove::TickTask(float DeltaTime)
{
	if (hitted)
	{
		interpAlpha += 1.f * interpolationSpeed * DeltaTime;

        enemyPosBeforeAttack = hitted->GetActorLocation() - UKismetMathLibrary::GetDirectionUnitVector(owner->GetActorLocation(), hitted->GetActorLocation()) * wolfEnemySeparation;


		currentPos = FMath::Lerp(posBeforeAttack, enemyPosBeforeAttack, lerpCurve->GetFloatValue(interpAlpha));
		owner->SetActorLocation(FVector(currentPos.X, currentPos.Y, posBeforeAttack.Z));


		currentRot = FMath::Lerp(rotBeforeAttack, rotIdeal, lerpCurve->GetFloatValue(interpAlpha * 2.f));
		owner->SetActorRotation(currentRot);


		//owner->AddActorWorldOffset((directionHit * (lessDistance / time)) * DeltaTime, true);
		//owner->AddActorWorldRotation((rotIdeal * (1 / time)) * DeltaTime, true);
	}

	if (!reachedEnemy && interpAlpha > 0.6f)
	{
		OnReach.Broadcast();
		reachedEnemy = true;
	}

	if (interpAlpha >= 1)
	{
		OnEnd.Broadcast();
		EndTask();
	}
}


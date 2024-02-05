// Created by pablo


#include "Game/HICameraManager.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Characters/VincentVolk/HIWerewolfController.h"
#include "DrawDebugHelpers.h"
#include "Game/Audio/HIAmbientSound.h"
#include "GameFramework/SpringArmComponent.h"
#include "HIGameData.h"
#include "Kismet/KismetMathLibrary.h"



AHICameraManager::AHICameraManager() :
	player(nullptr),
	datatable(nullptr),
	distanceFromPlayer(0.f),
	height(0.f),
	leftDeviation(0.f),
	interpolationSpeed(0.f),
	lerpCurve(nullptr),
	maxTopInclination(0.f),
	maxBottomInclination(0.f),
	distFindTarget(0.f),
	distLoseTarget(0.f),
	changeTargetDelay(0.f),
	targetedActor(nullptr),
	changetargetDelayTimer(0.f),
	hiWorld(nullptr),
	springArmLengInitRot(0.f)
{
	PrimaryActorTick.bCanEverTick = true;

	if (!werewolfController)
	{
		werewolfController = UHIGameData::HIGetPlayerController();
	}
}

AHICameraManager::~AHICameraManager()
{
	TargetEmpty();
}

void AHICameraManager::BeginPlay()
{
	Super::BeginPlay();

	UHIGameData::HISetCameraManager(this);

	if (!hiWorld)
	{
		hiWorld = UHIGameData::HIGetWerewolfWorld();
	}

	player = UHIGameData::HIGetPlayerWerewolf();

	currentCamView = CameraView::COMBAT;
	ChangeCameraView(CameraView::HUNT);
}

void AHICameraManager::ChangeCameraView(CameraView _view)
{
	switch (_view)
	{
	case CameraView::HUNT:
		if (currentCamView != CameraView::HUNT)
		{
			HIInitVars(0);

			camPos = FVector(0, leftDeviation, height);

			// HIScriptedCameraView();

			UHIGameData::HIGetSpeaker2D()->HIPlayHunt();

			currentCamView = _view;
			changingMode = true;
		}
		break;
	case CameraView::COMBAT:
		if (currentCamView != CameraView::COMBAT)
		{
			HIInitVars(1);
			camPos = FVector(0, leftDeviation, height);

			// HIScriptedCameraView();

			UHIGameData::HIGetSpeaker2D()->HIPlayCombat();

			currentCamView = _view;
			changingMode = true;
		}
		break;
	case CameraView::SCRIPTED:
		//       if (currentCamView != CameraView::SCRIPTED)
		//       {
		//          Row = datatable->FindRow<FHI_DT_Camera>(RowNames[2], ContextString, true);
		//          interpolationSpeed = Row->interpolationSpeed;
		// 
		//          interpAlpha = 0;
		//          currentCamView = _view;
		//          changingMode = true;
		//       }
		break;
	default:
		break;
	}
}

void AHICameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!player)
	{
		return;
	}

	if (!player->GetController())
	{
		return;
	}

	if (player->GetController()->GetControlRotation().Pitch > 180.f)
	{
		if (!buleanoWarro)
		{
			camDist = 360.f - player->GetController()->GetControlRotation().Pitch;
		}
		else
		{
			camDist = 0;
		}

	}

	if (changingMode && !buleanoWarro)
	{
		CameraMode(DeltaTime);
	}
	else
	{
		player->springArm->TargetArmLength = distanceFromPlayer + camDist * 8;
	}

	if (!centeredCamera)
	{
		CentrateCamera(DeltaTime);
	}

	//mov horizontal
	if (targetedActor)
	{
		TargetOn(DeltaTime);
		targetMode = true;
		targetSnapped = nullptr;

		if (distLoseTarget < (player->GetActorLocation() - targetedActor->GetActorLocation()).Size() || targetedActor->isDead)
		{
			targetedActor->targetEnemyReference->HISetTargetImageVisibility(ESlateVisibility::Collapsed);
			targetedActor = nullptr;
		}
	}
	else
	{
		if (targetMode)
		{
			TargetOff();
			targetMode = false;
		}

		if (targetSnapped)
		{
			TargetSnapped(DeltaTime);
		}
	}

	if (changetargetDelayTimer < changeTargetDelay)
	{
		changetargetDelayTimer += DeltaTime;
		changeTargetAllowed = false;
	}
	else
	{
		changeTargetAllowed = true;
	}

	//mov vertical
	if (UHIGameData::HIInCombat() && currentCamView == CameraView::HUNT)
	{
		ChangeCameraView(CameraView::COMBAT);
	}
	else if (!UHIGameData::HIInCombat() && currentCamView == CameraView::COMBAT)
	{
		if (postCombatTimer < 3)
		{
			postCombatTimer += DeltaTime;
		}
		else
		{
			ChangeCameraView(CameraView::HUNT);
			postCombatTimer = 0;
		}
	}
}

void AHICameraManager::CameraMode(float DeltaTime)
{
	if (currentCamView != CameraView::SCRIPTED)
	{
		FRotator changeRot = FRotator::ZeroRotator;

		interpAlpha += 1.f / interpolationSpeed;

		changeRot = FMath::Lerp(camInitRot, rotation, lerpCurve->GetFloatValue(interpAlpha));

		player->springArm->SocketOffset = FMath::Lerp(springArmSocInitRot, camPos, lerpCurve->GetFloatValue(interpAlpha));

		player->springArm->TargetArmLength = FMath::Lerp(springArmLengInitRot, distanceFromPlayer + camDist * 8, lerpCurve->GetFloatValue(interpAlpha));

		ViewPitchMin = 360.f - maxTopInclination;
		ViewPitchMax = maxBottomInclination;
		player->cineCamera->SetRelativeRotation(changeRot);

		if (interpAlpha >= 1)
		{
			changingMode = false;
		}
	}
	else
	{
		if (interpAlpha == 0.f)
		{
			werewolfController = UHIGameData::HIGetPlayerController();
		}

		interpAlpha += 1.f / interpolationSpeed;

		if (interpAlpha >= 1)
		{
			changingMode = false;
		}
	}
}

void AHICameraManager::CentrateCamera(float DeltaTime)
{
	if (changingMode == false)
	{
		if (player->springArm->bInheritYaw)
		{
			player->springArm->SetRelativeRotation(player->GetCapsuleComponent()->GetRelativeRotation());
			player->springArm->bInheritYaw = false;
		}

		FVector dir = player->GetActorForwardVector();
		FRotator view = player->springArm->GetRelativeRotation();
		view.Yaw = dir.Rotation().Yaw;

		FRotator changeRot = UKismetMathLibrary::RLerp(player->springArm->GetRelativeRotation(), player->GetActorRotation(), 0.5f, true);

		hiWorld->GetFirstPlayerController()->SetControlRotation(view);
		player->springArm->SetRelativeRotation(changeRot);

		timerToCenterCamera += DeltaTime;

		if (timerToCenterCamera > 0.25f)
		{
			if (player->springArm->bInheritYaw == false)
			{
				player->springArm->SetRelativeRotation(player->GetCapsuleComponent()->GetRelativeRotation());
				player->springArm->bInheritYaw = true;
			}

			centeredCamera = true;
			timerToCenterCamera = 0;
		}
	}
	else
	{
		centeredCamera = true;
		timerToCenterCamera = 0;
	}
}

void AHICameraManager::TargetDetection()
{
	TArray<FHitResult> hitResults;
	TArray<AHIEnemy*> HitActors;

	HISweepActors(hitResults);

	for (FHitResult Iter : hitResults)
	{
		HitActors.Add(Cast<AHIEnemy>(Iter.GetActor()));
	}

	float num = HitActors.Num();

	if (num > 0)
	{
		float dis = 0;
		float mindis = 0;

		AHIEnemy* closest = nullptr;

		for (int i = 0; i < num; ++i)
		{
			dis = (player->GetActorLocation() - HitActors[i]->GetActorLocation()).Size();

			if (mindis == 0 || dis < mindis)
			{
				if (FMath::Abs(player->GetActorLocation().Z - HitActors[i]->GetActorLocation().Z) < 50.f)
				{
					if (!HitActors[i]->HICharacterDead())
					{
						closest = HitActors[i];
						mindis = dis;
					}
				}
			}
		}

		targetedActor = closest;

		if (targetedActor && targetedActor->targetEnemyReference)
		{
			targetedActor->targetEnemyReference->HISetTargetImageVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
	}
	else
	{
		centeredCamera = false;
	}
}

void AHICameraManager::TargetChange(bool _rightSide)
{
	if (changeTargetAllowed && targetedActor)
	{
		TArray<FHitResult> hitResults;
		TArray<AActor*> HitActors;

		HISweepActors(hitResults);

		for (FHitResult Iter : hitResults)
		{
			HitActors.Add(Iter.GetActor());
		}

		float num = HitActors.Num();

		if (num > 1)
		{
			float ang = 0;
			float minAng = 0;

			AActor* closest = nullptr;

			float lastAng = (targetedActor->GetActorLocation() - player->GetActorLocation()).Rotation().Yaw;

			for (int i = 0; i < num; ++i)
			{
				if (HitActors[i] != targetedActor)
				{
					ang = (HitActors[i]->GetActorLocation() - player->GetActorLocation()).Rotation().Yaw;

					ang = ang - lastAng;

					if (_rightSide && ang < 0)
					{
						FMath::Abs(ang);

						if (minAng == 0 || ang < minAng)
						{
							if (FMath::Abs(player->GetActorLocation().Z - HitActors[i]->GetActorLocation().Z) < 50.f)
							{
								closest = HitActors[i];
								minAng = ang;
							}
						}
					}

					if (!_rightSide && ang > 0)
					{
						FMath::Abs(ang);

						if (minAng == 0 || ang < minAng)
						{
							if (FMath::Abs(player->GetActorLocation().Z - HitActors[i]->GetActorLocation().Z) < 50.f)
							{
								closest = HitActors[i];
								minAng = ang;
							}
						}
					}
				}
			}

			if (closest)
			{
				if (targetedActor->targetEnemyReference)
				{
					targetedActor->targetEnemyReference->HISetTargetImageVisibility(ESlateVisibility::Collapsed);
					targetedActor = Cast<AHIEnemy>(closest);
					if (targetedActor->targetEnemyReference)
					{
						targetedActor->targetEnemyReference->HISetTargetImageVisibility(ESlateVisibility::SelfHitTestInvisible);
						changetargetDelayTimer = 0;
					}
				}
			}
		}
	}
}

void AHICameraManager::TargetEmpty()
{
	targetedActor = nullptr;
}

void AHICameraManager::TargetSnapped(float DeltaTime)
{
	timerSnap = 0.f;
	targetSnapped = nullptr;
	player->springArm->bInheritYaw = true;
}

void AHICameraManager::HICenterCameraExecution(FRotator _targetRotation)
{
	HIBlockCameraInputRotation(true);
	player->springArm->SetRelativeRotation(_targetRotation);
	player->springArm->TargetArmLength = distanceFromPlayer + camDist * 8;
}

void AHICameraManager::HIBlockCameraInputRotation(bool _isBlocked)
{
	player->springArm->bInheritYaw = !_isBlocked;
	player->springArm->bInheritPitch = !_isBlocked;
	player->springArm->bInheritRoll = !_isBlocked;
}

void AHICameraManager::TargetOn(float DeltaTime)
{
	if (player->springArm->bInheritYaw)
	{
		player->springArm->SetRelativeRotation(player->GetCapsuleComponent()->GetRelativeRotation());
		player->springArm->bInheritYaw = false;
	}

	FVector dir = targetedActor->GetActorLocation() - player->GetActorLocation();
	FRotator view = player->springArm->GetRelativeRotation();
	view.Yaw = dir.Rotation().Yaw;

	FRotator changeRot = FMath::RInterpTo(player->springArm->GetRelativeRotation(), view, DeltaTime, 10.f);

	hiWorld->GetFirstPlayerController()->SetControlRotation(dir.Rotation());
	player->springArm->SetRelativeRotation(changeRot);
}

void AHICameraManager::TargetOff()
{
	player->springArm->bInheritYaw = true;

	int aux = 0;

	if (currentCamView == CameraView::HUNT) aux = 0;
	if (currentCamView == CameraView::COMBAT) aux = 1;
	if (currentCamView == CameraView::SCRIPTED) aux = 2;

	HIInitVars(aux);

	changingMode = true;
}

void AHICameraManager::HIInitVars(int _value)
{
	FString ContextString = TEXT("Data table context");
	TArray<FName> RowNames = datatable->GetRowNames();

	Row = datatable->FindRow<FHI_DT_Camera>(RowNames[_value], ContextString, true);
	rotation = Row->rotation;
	height = Row->height;
	distanceFromPlayer = Row->distanceFromPlayer;
	maxTopInclination = Row->maxTopInclination;
	maxBottomInclination = Row->maxBottomInclination;
	distFindTarget = Row->distFindTarget;
	distLoseTarget = Row->distLoseTarget;
	changeTargetDelay = Row->changeTargetDelay;
	leftDeviation = Row->leftDeviation;
	camInitRot = player->cineCamera->GetRelativeRotation();
	springArmSocInitRot = player->springArm->SocketOffset;
	springArmLengInitRot = player->springArm->TargetArmLength;
	lerpCurve = Row->lerpCurve;
	interpolationSpeed = Row->interpolationSpeed;
	interpAlpha = 0;
}

void AHICameraManager::HIScriptedCameraView()
{
	if (currentCamView == CameraView::SCRIPTED)
	{
		player->scriptedCamera->EndScriptedCamera();

		if (!werewolfController)
		{
			werewolfController = UHIGameData::HIGetPlayerController();
		}
		werewolfController->SetViewTargetWithBlend(player, 1.f);
	}
}

void AHICameraManager::HISweepActors(TArray<FHitResult>& _hitResult, ECollisionChannel _collisionChannel)
{
	if (hiWorld)
	{
		hiWorld->SweepMultiByChannel(_hitResult, player->GetActorLocation(), player->GetActorLocation(), FQuat::Identity, _collisionChannel, FCollisionShape::MakeSphere(distLoseTarget));

	}
}

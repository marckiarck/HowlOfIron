// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/HitArea/HitAreaActor.h"

// Sets default values
AHIHitAreaActor::AHIHitAreaActor() : hitAreaColor(FLinearColor())
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//niagaraParticleComponent = CreateDefaultSubobject<UNiagaraComponent>("NiagaraSystemComponent");
	rayLength = 1000.f;

	hitAreaAimActived = false;
}

void AHIHitAreaActor::HISetEmiter(USceneComponent* emiter, FName emiterSocket)
{
	hitAreaEmiter = emiter;
	emiterSocketName = emiterSocket;

	FAttachmentTransformRules attachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
	AttachToComponent(emiter, attachmentRules, emiterSocketName);

	hitAreaAimActived = true;
}

void AHIHitAreaActor::BeginPlay()
{
	Super::BeginPlay();

	elapsedLifeTime = 0.f;

	lastFrameRotation = 0.f;
}

void AHIHitAreaActor::HIInitializeNiagaraSystem()
{
	if (niagaraParticleComponent == nullptr)
	{
		if (niagaraSystem)
		{
			if (hitAreaEmiter && spawnMode == ATTACHED)
			{
				niagaraParticleComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(niagaraSystem, hitAreaEmiter, emiterSocketName, attachOffset, FRotator(0.f, 0.f, 0.f), FVector(1.f, 1.f, 1.f), EAttachLocation::KeepRelativeOffset, true, ENCPoolMethod::AutoRelease);
			}
			else
			{
				niagaraParticleComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), niagaraSystem, GetActorLocation());
			}


			hitAreaColor.R = 0.0f;
			hitAreaColor.G = 1.f;
			hitAreaColor.B = 0.f;
			hitAreaColor.A = 0.f;


			HIUpdateNiagaraParameters();
			niagaraParticleComponent->SetNiagaraVariableFloat(LOOP_DURATION_VARIABLE, lifeTime);

		}
	}

}

void AHIHitAreaActor::HIUpdateNiagaraParameters()
{

	niagaraParticleComponent->SetNiagaraVariableVec3(START_POSITION_VARIABLE, GetActorLocation());

	if (hitObjetive)
	{
		FVector hitAreaDirection;
		FHitResult hitResult = FHitResult();
		FCollisionQueryParams params = FCollisionQueryParams();
		params.AddIgnoredActor(hitAreaEmiter->GetOwner());
		DirectionShootPoint = hitObjetive->GetActorLocation();
		GetWorld()->LineTraceSingleByChannel(hitResult, GetActorLocation(), hitObjetive->GetActorLocation(), GAME_TRACE_SHOOT, params);
		if (hitResult.bBlockingHit)
		{
			hitAreaDirection = hitResult.ImpactPoint - GetActorLocation();
			if (hitResult.Actor == UHIGameData::HIGetPlayerWerewolf())
			{
				hitAreaDirection += (hitResult.Component->Bounds.Origin - hitResult.ImpactPoint);
			}

			niagaraParticleComponent->SetNiagaraVariableVec3(END_POSITION_VARIABLE, FVector(hitAreaDirection.X, hitAreaDirection.Y, hitAreaDirection.Z + 40.f));
		}
		else
		{
			hitAreaDirection = (hitObjetive->GetActorLocation() - hitAreaEmiter->GetComponentLocation()).GetSafeNormal();
			niagaraParticleComponent->SetNiagaraVariableVec3(END_POSITION_VARIABLE, hitAreaDirection * rayLength);
		}

	}
	else
	{
		FVector hitAreaDirection;
		FHitResult hitResult = FHitResult();
		FCollisionQueryParams params = FCollisionQueryParams();
		if (hitAreaEmiter)
		{
			params.AddIgnoredActor(hitAreaEmiter->GetOwner());
		}
		GetWorld()->LineTraceSingleByChannel(hitResult, GetActorLocation(), DirectionShootPoint, GAME_TRACE_SHOOT, params);
		if (hitResult.bBlockingHit)
		{
			hitAreaDirection = hitResult.ImpactPoint - GetActorLocation();
			if (hitResult.Actor == UHIGameData::HIGetPlayerWerewolf())
			{
				hitAreaDirection += (hitResult.Component->Bounds.Origin - hitResult.ImpactPoint);
			}

			niagaraParticleComponent->SetNiagaraVariableVec3(END_POSITION_VARIABLE, FVector(hitAreaDirection.X, hitAreaDirection.Y, hitAreaDirection.Z + 40.f));
		}
		else {
			hitAreaDirection = (DirectionShootPoint - hitAreaEmiter->GetComponentLocation()).GetSafeNormal();
			niagaraParticleComponent->SetNiagaraVariableVec3(END_POSITION_VARIABLE, hitAreaDirection * rayLength);
		}
	}



	niagaraParticleComponent->SetNiagaraVariableLinearColor(HIT_AREA_COLOR_VARIABLE, hitAreaColor);
	niagaraParticleComponent->SetNiagaraVariableFloat(COLOR_R_VARIABLE, hitAreaColor.R);
	niagaraParticleComponent->SetNiagaraVariableFloat(COLOR_G_VARIABLE, hitAreaColor.G);
	niagaraParticleComponent->SetNiagaraVariableFloat(COLOR_B_VARIABLE, hitAreaColor.B);


	if (hitObjetive)
	{
		HIUpdateNiagaraRotation(); //Not used for now
	}

}

void AHIHitAreaActor::HIUpdateNiagaraRotation()
{
	FVector xAxis = FVector(1.0f, 0.f, 0.f);
	FVector objetiveDirectionNorm = (hitObjetive->GetActorLocation() - GetActorLocation()).GetSafeNormal(0.f);
	float dotProduct = FVector::DotProduct(xAxis, objetiveDirectionNorm);
	float angleToObjetive = FMath::RadiansToDegrees(FMath::Acos(dotProduct));
	if (objetiveDirectionNorm.Y < 0.f)
	{
		angleToObjetive = 360.f - angleToObjetive;
	}

	FVector rotationVector = FVector(0.f, 0.f, angleToObjetive / 360.f);
	niagaraParticleComponent->SetNiagaraVariableVec3(ROTATION_VARIABLE, rotationVector);

	float angleDiference = angleToObjetive - lastFrameRotation;
	if (angleDiference < -180.f)
	{
		angleDiference = 0.f;
	}
	else if (angleDiference > 180.f)
	{
		angleDiference = 0.f;
	}

	niagaraParticleComponent->SetNiagaraVariableVec3(ROTATION_SPEED_VARIABLE, FVector(0.f, 0.f, angleDiference));

	lastFrameRotation = angleToObjetive;
}

void AHIHitAreaActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	HIInitializeNiagaraSystem();

	niagaraParticleComponent->SetNiagaraVariableFloat(ELAPSED_TIME_VARIABLE, elapsedLifeTime);

	if (elapsedLifeTime > lifeTime)
	{
		StopHitArea();
		return;
	}


	if (hitAreaAimActived)
	{
		float colorVariation = DeltaTime / colorChangeDuration;
		hitAreaColor.R = FMath::Min(hitAreaColor.R + colorVariation, 1.f);

		if (directShoot)
		{
			hitAreaColor.G = FMath::Max(hitAreaColor.G - colorVariation, 0.f);
		}
	}
	else
	{
		if (this->followMode == FollowMode::STOP_WHEN_AIM_ENDS)
		{
			hitObjetive = nullptr;
			niagaraParticleComponent->SetNiagaraVariableVec3(ROTATION_SPEED_VARIABLE, FVector(0.f, 0.f, 0.f));

			if (spawnMode == ATTACHED)
			{
				niagaraParticleComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			}
		}

		if (killMode == KILL_WHEN_STOP_AIM)
		{
			niagaraParticleComponent->DestroyInstance();
		}

		hitAreaColor = FLinearColor::Red;

	}

	HIUpdateNiagaraParameters();

	elapsedLifeTime += DeltaTime;
}

void AHIHitAreaActor::StopHitArea()
{
	if (niagaraParticleComponent)
	{
		niagaraParticleComponent->DestroyInstance();
	}

	Destroy();
}


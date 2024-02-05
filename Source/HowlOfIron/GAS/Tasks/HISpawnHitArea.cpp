// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HISpawnHitArea.h"

UHISpawnHitArea::UHISpawnHitArea()
{
	bTickingTask = true;
}

UHISpawnHitArea* UHISpawnHitArea::HISpawnHitArea(UGameplayAbility* OwningAbility, TSubclassOf<AHIHitAreaActor> hitAreaActor, float areaHitLifeTime, float objetiveAimDuration, float areaHitRayLength, USceneComponent* componentAttachedTo, FName attachedToSocketName, FVector attachOffset, AActor* hitObjetive, FVector HitPoint)
{
	UHISpawnHitArea* returnedTask = NewAbilityTask<UHISpawnHitArea>(OwningAbility);

	returnedTask->hitAreaClass = hitAreaActor;
	returnedTask->lifeTime = areaHitLifeTime;
	returnedTask->aimDuration = objetiveAimDuration;
	returnedTask->rayLength = areaHitRayLength;
	returnedTask->emiterComponent = componentAttachedTo;
	returnedTask->emiterSocketName = attachedToSocketName;
	returnedTask->attachOffset = attachOffset;
	returnedTask->objetive = hitObjetive;
	returnedTask->ShootHitPoint = HitPoint;

	return returnedTask;
}

void UHISpawnHitArea::Activate()
{
	spawnedHitArea = Cast<AHIHitAreaActor>(UHIGameData::HIGetWerewolfWorld()->SpawnActor(hitAreaClass));

	if (emiterComponent)
	{
		spawnedHitArea->HISetEmiter(emiterComponent, emiterSocketName);
	}
	
	spawnedHitArea->lifeTime = lifeTime;
	spawnedHitArea->rayLength = rayLength;
	spawnedHitArea->hitObjetive = objetive;
	spawnedHitArea->colorChangeDuration = aimDuration;
	spawnedHitArea->attachOffset = attachOffset;
	spawnedHitArea->DirectionShootPoint = ShootHitPoint;

	onStopAimUsed = false;

	OnSpawned.Broadcast(spawnedHitArea);
}

void UHISpawnHitArea::TickTask(float DeltaTime)
{
	if (elapsedTime > lifeTime)
	{
		if (onStopAimUsed == false)
		{
			OnStopAim.Broadcast();
		}

		OnHitAreaDestroy.Broadcast();
		EndTask();
	}
	else {

		if (elapsedTime > aimDuration)
		{
			if (spawnedHitArea->hitAreaAimActived)
			{
				spawnedHitArea->hitAreaAimActived = false;
				OnStopAim.Broadcast();
				onStopAimUsed = true;
			}
		}
	}

	elapsedTime += DeltaTime;
}


void UHISpawnHitArea::OnDestroy(bool bInOwnerFinished)
{
	spawnedHitArea->StopHitArea();

	Super::OnDestroy(bInOwnerFinished);
}

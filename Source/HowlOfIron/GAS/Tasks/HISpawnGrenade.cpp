// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HISpawnGrenade.h"
#include "Game/HIGameData.h"

UHISpawnGrenade::UHISpawnGrenade() : assignedOwnerSkeletalMesh(nullptr), assignedSocketName(TEXT("None"))
{

}

UHISpawnGrenade* UHISpawnGrenade::HISpwanGrenade(UGameplayAbility* OwningAbility, TSubclassOf<AHIGrenade> grenadeType, FVector spawnPosition, FVector grenadeObjetive)
{
	UHISpawnGrenade* returnedTask = NewAbilityTask<UHISpawnGrenade>(OwningAbility);

	returnedTask->grenadeClass = grenadeType;
	returnedTask->objetivePosition = grenadeObjetive;
	returnedTask->spawnLocation = spawnPosition;

	return returnedTask;
}

void UHISpawnGrenade::Activate()
{
	spawnedGrenade = Cast<AHIGrenade>(UHIGameData::HIGetWerewolfWorld()->SpawnActor(grenadeClass));
	spawnedGrenade->SetActorLocation(spawnLocation);
	spawnedGrenade->SetGrenadeObjective(objetivePosition);

	spawnedGrenade->onGrenadeEndLaunch.AddDynamic(this, &UHISpawnGrenade::OnGrenadeEndLaunch);
}

void UHISpawnGrenade::OnGrenadeEndLaunch()
{
	onEndLaunch.Broadcast(spawnedGrenade);
	EndTask();
}


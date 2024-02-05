// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HIThrowGrabbedEnemy.h"

UHIThrowGrabbedEnemy* UHIThrowGrabbedEnemy::HIThrowEnemyGrabbed(UGameplayAbility* OwningAbility)
{
	UHIThrowGrabbedEnemy* returnedTask = NewAbilityTask<UHIThrowGrabbedEnemy>(OwningAbility);

	return returnedTask;
}

void UHIThrowGrabbedEnemy::Activate()
{
	AHIWerewolf* werewolf = Cast<AHIWerewolf>(GetAvatarActor());
	werewolf->HIThrowEnemyGrabbed();
	OnActive.Broadcast(werewolf->enemygrabbed);
}

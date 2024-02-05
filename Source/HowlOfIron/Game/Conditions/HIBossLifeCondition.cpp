// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Conditions/HIBossLifeCondition.h"
#include <Characters/Enemies/HIEnemy.h>

bool UHIBossLifeCondition::HICheckCondition()
{
	AHIEnemy* boss = UHIGameData::HIGetBoss();

	if (boss)
	{
		float health = boss->HIGetAttributes()->Gethealth();
		float maxHealth = boss->HIGetAttributes()->GetmaxHealth();

		if (health / maxHealth <= lifePercent)
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	return false;
}
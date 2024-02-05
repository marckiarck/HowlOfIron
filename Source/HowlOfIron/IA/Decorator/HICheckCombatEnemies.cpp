// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Decorator/HICheckCombatEnemies.h"
#include "Game/HIGameData.h"

UHICheckCombatEnemies::UHICheckCombatEnemies()
{

}

UHICheckCombatEnemies::~UHICheckCombatEnemies()
{

}

bool UHICheckCombatEnemies::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	TArray<AHIEnemy*> combatEnemiesArray = UHIGameData::HIGetCombatEnemiesArray();
	int currentCombatEnemies = combatEnemiesArray.Num();

	AHIEnemyController* enemyController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
	AHIEnemy* enemy = Cast<AHIEnemy>(enemyController->GetPawn());


	if (currentCombatEnemies == 0)
	{
		return true;
	}

	if (currentCombatEnemies > numCombatEnemies)
	{
		if (combatEnemiesArray.Contains(enemy) == false)
		{
			return false;
		}

		if (combatEnemiesArray[numCombatEnemies] == enemy)
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

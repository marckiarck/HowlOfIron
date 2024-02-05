// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Decorator/HICheckPatrolAnims.h"

bool UHICheckPatrolAnims::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AHIEnemyController* enemyController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
	AHIEnemy* enemy = Cast<AHIEnemy>(enemyController->GetPawn());


	if (checkAlertAnim)
	{
		if (enemy->patrolReference->alertAnim == false)
		{
			enemy->patrolReference->alertAnim = true;
			return true;
		}

		return false;
	}

	if (checkCallAnim)
	{
		if (enemy->patrolReference->combatAnim == false)
		{
			enemy->patrolReference->combatAnim = true;
			return true;
		}

		return false;
	}

	return false;
}
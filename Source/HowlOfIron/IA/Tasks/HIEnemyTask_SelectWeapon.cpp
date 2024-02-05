// Fill out your copyright notice in the Description page of Project Settings.


#include "HIEnemyTask_SelectWeapon.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Enemies/HIEnemy.h"
#include "Characters/Enemies/HIEnemyAccessory.h"
#include "Characters/Enemies/HIEnemyController.h"
#include "Game/HIGameData.h"
#include "HIMacros.h"


EBTNodeResult::Type UHIEnemyTask_SelectWeapon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AHIEnemyController* enemyController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
	AHIEnemy* enemy = enemyController->GetPawn<AHIEnemy>();
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();

	AHIEnemyAccessory* defaultWeapon = nullptr;
	AHIEnemyAccessory* weaponToChange = nullptr;

	for (AHIEnemyAccessory* enemyAccessory : enemy->accessories)
	{
		if (enemyAccessory->isWeapon)
		{
			if (enemyAccessory->weaponCondition.conditionType == WeaponConditionType::NO_CONDITION)
			{
				defaultWeapon = enemyAccessory;
			}
			else if (enemyAccessory->weaponCondition.conditionType == WeaponConditionType::INVULNERABILITY_STATUS)
			{
				bool isInvulnerable;
				CHECK_HAS_TAG(enemy->GetAbilitySystemComponent(), INMUNITY_TAG, isInvulnerable);
				if (isInvulnerable)
				{
					weaponToChange = enemyAccessory;
					break; // invulnerable has more weight than distance condition
				}
			}
			else if (enemyAccessory->weaponCondition.conditionType == WeaponConditionType::DISTANCE_TO_WEREWOLF)
			{
				AActor* comparedActor = Cast<AActor>(blackboard->GetValueAsObject("Werewolf"));
				if (comparedActor)
				{
					float distanceToComparedActor = (enemy->GetActorLocation() - comparedActor->GetActorLocation()).Size();
					if (HICheckDistance(distanceToComparedActor, enemyAccessory->weaponCondition) && !weaponToChange) // !weaponToChange because we want first accessory that meets the distance condition
					{
						weaponToChange = enemyAccessory;
					}
				}
			}
		}
	}

	weaponToChange = (weaponToChange) ? weaponToChange : defaultWeapon;
	if (weaponToChange)
	{
		enemy->HIChangeWeapon(weaponToChange->accessoryID);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

FString UHIEnemyTask_SelectWeapon::GetStaticDescription() const
{
    return FString(TEXT("Change weapon of the enemy"));
}

bool UHIEnemyTask_SelectWeapon::HICheckDistance(float _distance, const FHIWeaponConditionStruct& _weaponCondition) const
{
	switch (_weaponCondition.comparisonType)
	{
	case EQUALS:
	{
		if (_distance == _weaponCondition.distance)
		{
			return true;
		}
	}
	break;

	case LESS_THAN:
	{
		if (_distance < _weaponCondition.distance)
		{
			return true;
		}
	}
	break;

	case LESS_EQUAL:
	{
		if (_distance <= _weaponCondition.distance)
		{
			return true;
		}
	}
	break;

	case MORE_THAN:
	{
		if (_distance > _weaponCondition.distance)
		{
			return true;
		}
	}
	break;

	case MORE_EQUAL:
	{
		if (_distance >= _weaponCondition.distance)
		{
			return true;
		}
	}
	break;

	case BETWEEN:
	{
		if (_distance >= _weaponCondition.minorDistance && _distance <= _weaponCondition.mayorDistance)
		{
			return true;
		}
	}
	break;
	}

	return false;
}
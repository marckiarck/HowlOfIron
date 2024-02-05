// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Characters/Enemies/HIWeaponConditionStruct.h"
#include "HIEnemyTask_SelectWeapon.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHIEnemyTask_SelectWeapon : public UBTTaskNode
{
    GENERATED_BODY()

public:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
    virtual FString GetStaticDescription() const override;

private:
	bool HICheckDistance(float _distance, const FHIWeaponConditionStruct& _weaponCondition) const;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "HIEnemyTask_RemoveTag.generated.h"

/**
 * 
 */
UCLASS()
class HOWLOFIRON_API UHIEnemyTask_RemoveTag : public UBTTaskNode
{
	GENERATED_BODY()
	
	public:
	UPROPERTY(EditAnywhere)
	FGameplayTagContainer containerGameplayTags;
	public:

        virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

        virtual FString GetStaticDescription() const override;


};

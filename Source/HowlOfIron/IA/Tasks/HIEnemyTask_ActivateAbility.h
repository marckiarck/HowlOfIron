// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "HIEnemyTask_ActivateAbility.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHIEnemyTask_ActivateAbility : public UBTTaskNode
{
    GENERATED_BODY()
public:

public:

// UPROPERTY(EditAnywhere,BlueprintReadOnly)
//     TSubclassOf<UGameplayEffect> shootgameplayEffect;

UPROPERTY(EditAnywhere, BlueprintReadOnly)
FGameplayTag tagToAdd;


protected:

private:

public:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
    virtual FString GetStaticDescription() const override;
protected:

private:

};

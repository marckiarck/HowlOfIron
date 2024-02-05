// @AUTHOR: Carlos

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "HIEnemyTask_ActivateShootAbility.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHIEnemyTask_ActivateShootAbility : public UBTTaskNode
{
    GENERATED_BODY()

public:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
    virtual FString GetStaticDescription() const override;

};

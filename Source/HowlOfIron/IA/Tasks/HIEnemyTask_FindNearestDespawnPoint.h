// @AUTHOR: Carlos Fernandez

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "HIEnemyTask_FindNearestDespawnPoint.generated.h"


UCLASS()
class HOWLOFIRON_API UHIEnemyTask_FindNearestDespawnPoint : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	virtual FString GetStaticDescription() const override;

};

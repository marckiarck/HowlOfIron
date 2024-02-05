// @AUTHORS: Pablo, Guillermo 

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "HITask_MoveToAvoidance.generated.h"

/**
 *
 */
 class AHIEnemyController;

UCLASS()
class HOWLOFIRON_API UHITask_MoveToAvoidance : public UBTTask_MoveTo
{
	GENERATED_BODY()

public:
	UHITask_MoveToAvoidance(const FObjectInitializer& ObjectInitializer);
	~UHITask_MoveToAvoidance();

public:
	AHIEnemyController* enemyController;



protected:


private:


public:


protected:


private:


};

// Created by pablo

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Characters/Enemies/HIEnemyController.h"
#include "Characters/Enemies/HIEnemy.h"
#include "HIEnemyTask_MoveToTarget.generated.h"


UCLASS()
class HOWLOFIRON_API UHIEnemyTask_MoveToTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UHIEnemyTask_MoveToTarget() {};
	~UHIEnemyTask_MoveToTarget() { UE_LOG(LogTemp, Log, TEXT("Enemy task deleted.")); }

public:

protected:

private:
	UPROPERTY()
		UBlackboardComponent* blackboard;

	UPROPERTY()
		AHIEnemyController* muttonController;

	UPROPERTY()
		AHIEnemy* mutton;

	UPROPERTY()
		FBlackboardKeySelector key;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	virtual FString GetStaticDescription() const override;

protected:

private:

};

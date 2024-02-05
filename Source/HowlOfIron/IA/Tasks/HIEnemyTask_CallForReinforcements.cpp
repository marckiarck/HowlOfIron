// @AUTHOR: Carlos Fernandez

#include "HIEnemyTask_CallForReinforcements.h"

EBTNodeResult::Type UHIEnemyTask_CallForReinforcements::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AHIEnemyController* enemyController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
	AHIEnemy* enemy = enemyController->GetPawn<AHIEnemy>();

	enemy->patrolReference->HICallForReinforcements(enemy);
	return EBTNodeResult::Succeeded;

}

FString UHIEnemyTask_CallForReinforcements::GetStaticDescription() const
{
	return TEXT("Call for reinforcements");
}

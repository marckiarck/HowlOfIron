// @AUTHOR: Carlos Fernandez

#include "HIEnemyTask_DespawnEnemy.h"
#include "Characters/Enemies/HIEnemy.h"
#include "Characters/Enemies/HIEnemyController.h"
#include "IA/HIMasterSecurity.h"
#include "IA/HIPatrol.h"


EBTNodeResult::Type UHIEnemyTask_DespawnEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AHIEnemyController* enemyController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
	AHIEnemy* enemy = enemyController->GetPawn<AHIEnemy>();

	enemy->patrolReference->HIRemoveEnemyFromPatrol(enemy);

	enemy->masterSecurity->objectPooler->DespawnItem(enemy);

	return EBTNodeResult::Succeeded;
}

FString UHIEnemyTask_DespawnEnemy::GetStaticDescription() const
{
	return TEXT("Despawn enemy");
}

// Created by pablo


#include "HIEnemyTask_MoveToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


//moves the pawn to the location taking the the info from the blackboard
EBTNodeResult::Type UHIEnemyTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	blackboard = OwnerComp.GetBlackboardComponent();
	muttonController = Cast<AHIEnemyController>(OwnerComp.GetOwner());
	mutton = Cast<AHIEnemy>(muttonController->GetPawn());


	if (!mutton->GetCharacterMovement()->bOrientRotationToMovement && !mutton->inCombat)
	{
		mutton->GetCharacterMovement()->bOrientRotationToMovement = true;
		mutton->bUseControllerRotationPitch = true;
		mutton->bUseControllerRotationYaw = true;
		mutton->bUseControllerRotationRoll = true;
	}

	AActor* target = Cast<AActor>(blackboard->GetValueAsObject("TargetToFollow"));

	UAIBlueprintHelperLibrary::CreateMoveToProxyObject(GetWorld(), muttonController->GetPawn(),
		target->GetActorLocation(), target, 1, true);

	return EBTNodeResult::Succeeded;
}


//describes the task in the behavior tree
FString UHIEnemyTask_MoveToTarget::GetStaticDescription() const
{
	return TEXT("Move to a location");
}

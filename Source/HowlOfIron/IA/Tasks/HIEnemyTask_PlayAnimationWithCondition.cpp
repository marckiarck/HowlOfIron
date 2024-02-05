// Copyright Epic Games, Inc. All Rights Reserved.
// @AUTHOR: Carlos Fernandez (modification of Engine\Source\Runtime\AIModule\Private\BehaviorTree\Tasks\BTTask_PlayAnimation.cpp)

#include "HIEnemyTask_PlayAnimationWithCondition.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "VisualLogger/VisualLogger.h"

//----------------------------------------------------------------------//
// UHIEnemyTask_PlayAnimationWithCondition
//----------------------------------------------------------------------//
UHIEnemyTask_PlayAnimationWithCondition::UHIEnemyTask_PlayAnimationWithCondition(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Play Animation With Condition";
	// instantiating to be able to use Timers
	bCreateNodeInstance = true;

	bLooping = false;
	bNonBlocking = false;

	TimerDelegate = FTimerDelegate::CreateUObject(this, &UHIEnemyTask_PlayAnimationWithCondition::OnAnimationTimerDone);
	PreviousAnimationMode = EAnimationMode::AnimationBlueprint;
}

EBTNodeResult::Type UHIEnemyTask_PlayAnimationWithCondition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* const MyController = OwnerComp.GetAIOwner();
	EBTNodeResult::Type Result = EBTNodeResult::Failed;

	// reset timer handle
	TimerHandle.Invalidate();
	MyOwnerComp = &OwnerComp;

	if (AnimationToPlay && MyController && MyController->GetPawn())
	{
		// HIModification: If playAnimationCondition is not set, continue the bhv tree execution
		if (!MyController->GetBlackboardComponent()->GetValueAsBool(playAnimationCondition.SelectedKeyName))
		{
			return EBTNodeResult::Succeeded;
		}

		USkeletalMeshComponent* SkelMesh = nullptr;
		ACharacter* const MyCharacter = Cast<ACharacter>(MyController->GetPawn());
		if (MyCharacter)
		{
			SkelMesh = MyCharacter->GetMesh();
		}
		else
		{
			SkelMesh = MyController->GetPawn()->FindComponentByClass<USkeletalMeshComponent>();
		}

		if (SkelMesh != nullptr)
		{
			PreviousAnimationMode = SkelMesh->GetAnimationMode();
			CachedSkelMesh = SkelMesh;

			SkelMesh->PlayAnimation(AnimationToPlay, bLooping);
			const float FinishDelay = AnimationToPlay->GetMaxCurrentTime();

			if (bNonBlocking == false && FinishDelay > 0)
			{
				if (bLooping == false)
				{
					MyController->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, FinishDelay, /*bLoop=*/false);
				}
				Result = EBTNodeResult::InProgress;
			}
			else
			{
				UE_CVLOG(bNonBlocking == false, MyController, LogBehaviorTree, Log, TEXT("%s> Instant success due to having a valid AnimationToPlay and Character with SkelMesh, but 0-length animation"), *GetNodeName());
				// we're done here, report success so that BT can pick next task
				Result = EBTNodeResult::Succeeded;
			}
		}
	}

	return Result;
}

EBTNodeResult::Type UHIEnemyTask_PlayAnimationWithCondition::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* const MyController = OwnerComp.GetAIOwner();

	if (AnimationToPlay && MyController && TimerHandle.IsValid())
	{
		MyController->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}

	TimerHandle.Invalidate();

	CleanUp(OwnerComp);

	return EBTNodeResult::Aborted;
}

FString UHIEnemyTask_PlayAnimationWithCondition::GetStaticDescription() const
{
	return FString::Printf(TEXT("%s: '%s'"), *Super::GetStaticDescription(), *GetNameSafe(AnimationToPlay)
		, bLooping ? TEXT(", looping") : TEXT("")
		, bNonBlocking ? TEXT(", non-blocking") : TEXT("blocking"));
}

void UHIEnemyTask_PlayAnimationWithCondition::OnAnimationTimerDone()
{
	if (MyOwnerComp)
	{
		CleanUp(*MyOwnerComp);
		FinishLatentTask(*MyOwnerComp, EBTNodeResult::Succeeded);
	}
}

void UHIEnemyTask_PlayAnimationWithCondition::CleanUp(UBehaviorTreeComponent& OwnerComp)
{
	if (CachedSkelMesh != nullptr && PreviousAnimationMode == EAnimationMode::AnimationBlueprint)
	{
		CachedSkelMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	}
}

#if WITH_EDITOR

FName UHIEnemyTask_PlayAnimationWithCondition::GetNodeIconName() const
{
	return FName("BTEditor.Graph.BTNode.Task.PlaySound.Icon");
}

#endif	// WITH_EDITOR

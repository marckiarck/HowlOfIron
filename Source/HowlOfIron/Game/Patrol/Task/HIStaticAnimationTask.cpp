// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Patrol/Task/HIStaticAnimationTask.h"
#include "Characters/Enemies/HIEnemy.h"





void UHIStaticAnimationTask::HIStartTask(AHIEnemy* _enemy, AHIPatrolPoint* _waypoint)
{
	Super::HIStartTask(_enemy, _waypoint);
	elapsedTime = 0.f;

	PreviousAnimationMode = EAnimationMode::AnimationBlueprint;


	PreviousAnimationMode = enemy->GetMesh()->GetAnimationMode();
	chachedSkeletalMesh = enemy->GetMesh();



	if (isTalkPoint && nearPoint && nearPoint->HIGetEnemyReference() && !nearPoint->HIGetEnemyReference()->HICharacterDead())
	{
		if (talkAnim)
		{

		chachedSkeletalMesh->PlayAnimation(talkAnim, false);
		toEndTime = talkAnim->GetMaxCurrentTime();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("playeo animacion doble")));;
		}
		else
		{
			HIEndTask();
		}
	}
	else
	{
		if (singleAnim != nullptr)
		{

		chachedSkeletalMesh->PlayAnimation(singleAnim, false);
		toEndTime = singleAnim->GetMaxCurrentTime();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("playeo animacion single")));	
		}
		else
		{
			HIEndTask();
		}

	}



}

void UHIStaticAnimationTask::HIUpdateTask(float DeltaTime)
{
	//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Blue, FString::Printf(TEXT("Update task")));

	if (HIIsExecuting())
	{
		elapsedTime += DeltaTime;
		FVector cosa = enemy->GetActorLocation();
		if (elapsedTime >= toEndTime)
		{			
			HIEndTask();
		}
		
	}
}



void UHIStaticAnimationTask::HIEndTask()
{

	FVector cosa = enemy->GetActorLocation();
	HICleanUpAnimation();
	Super::HIEndTask();
}




void UHIStaticAnimationTask::HICleanUpAnimation()
{
	if (chachedSkeletalMesh != nullptr && PreviousAnimationMode == EAnimationMode::AnimationBlueprint)
	{
		chachedSkeletalMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	}
}


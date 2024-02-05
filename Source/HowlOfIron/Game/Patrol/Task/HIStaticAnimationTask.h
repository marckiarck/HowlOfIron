// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Patrol/Task/HIWaypointTask.h"
#include "HIStaticAnimationTask.generated.h"

class AHIEnemy;

/**
 * 
 */
UCLASS()
class HOWLOFIRON_API UHIStaticAnimationTask : public UHIWaypointTask
{
	GENERATED_BODY()
	
public:






public:

protected:

private:

	UPROPERTY(EditAnywhere, Category = "Animations")
		UAnimationAsset* singleAnim;

	UPROPERTY(EditAnywhere, Category = "Animations")
		bool isTalkPoint;

	UPROPERTY(EditAnywhere, Category = "Animations", meta = (EditCondition = "isTalkPoint == true", EditConditionHides))
		UAnimationAsset* talkAnim;


	UPROPERTY(EditAnywhere, Category = "Animations", meta = (EditCondition = "isTalkPoint == true", EditConditionHides))
		AHIPatrolPoint* nearPoint;


	EAnimationMode::Type PreviousAnimationMode;

	UPROPERTY()
		float toEndTime = 0.f;

	float elapsedTime = 0.f;

	UPROPERTY(Transient)
		USkeletalMeshComponent* chachedSkeletalMesh;


public:





protected:



	virtual void HIStartTask(AHIEnemy* _enemy, AHIPatrolPoint* _waypoint) override;


	virtual void HIUpdateTask(float DeltaTime) override;

	virtual void HIEndTask() override;

private:



	void HICleanUpAnimation();

};

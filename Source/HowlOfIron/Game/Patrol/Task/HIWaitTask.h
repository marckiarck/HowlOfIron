// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HIWaypointTask.h"


#include "HIWaitTask.generated.h"

class AHIEnemy;
class UBTTaskNode;
class UBehaviorTreeComponent;

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class HOWLOFIRON_API UHIWaitTask : public UHIWaypointTask
{
    GENERATED_BODY()

public:
    UHIWaitTask();



public:
    UPROPERTY(EditAnywhere, Category = "WaitPoint")
        float waitTime;


    UPROPERTY(EditAnywhere, Category = "WaitPoint")
        float rotationSpeed;

protected:

private:


    UPROPERTY()
        float elapsedWait;



public:

protected:


	virtual void HIStartTask(AHIEnemy* _enemy, AHIPatrolPoint* _waypoint) override;


	virtual void HIUpdateTask(float DeltaTime) override;


private:

};

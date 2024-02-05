// @AUTHORS: Pablo, Guillermo Suárez

#include "HIEnemyController.h"
// #include "Navigation/CrowdFollowingComponent.h"
#include "DetourCrowdAIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "HIEnemy.h"
#include "IA/HICrowdFollowingComponent.h"


AHIEnemyController::AHIEnemyController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UHICrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
    crowdCollisionQueryRange = 1500.f;
    crowdSeparationWeight = 2.f;
}

void AHIEnemyController::BeginPlay()
{
    Super::BeginPlay();

    crowdFollowingComponent = Cast<UHICrowdFollowingComponent>(GetPathFollowingComponent());
    if (crowdFollowingComponent)
    {
        crowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);
        crowdFollowingComponent->SetCrowdCollisionQueryRange(crowdCollisionQueryRange, true);
        crowdFollowingComponent->SetCrowdSeparationWeight(crowdSeparationWeight, true);     
    }
}

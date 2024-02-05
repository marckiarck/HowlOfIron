// @AUTHORS: Pablo, Guillermo Suárez
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/UObjectGlobals.h"
#include "AIController.h"
#include "HIEnemyController.generated.h"

class UHICrowdFollowingComponent;

UCLASS(BlueprintType, Blueprintable)
class HOWLOFIRON_API AHIEnemyController : public AAIController
{
    GENERATED_BODY()


public:
    AHIEnemyController(const FObjectInitializer& ObjectInitializer);
    ~AHIEnemyController() { UE_LOG(LogTemp, Log, TEXT("EnemyController script deleted.")); }

public:
    UPROPERTY(EditAnywhere)
        float hitRadius = 100.f;

    UPROPERTY(VisibleAnywhere)
        int waypointIndex = 0;

    // Radio externo para comprobar cuando tienen que modificar su direccion
    UPROPERTY(EditAnywhere, Category = "Crowd Following")
        float crowdCollisionQueryRange;

    // No subir a mas de 6.0
    UPROPERTY(EditAnywhere, Category = "Crowd Following")
        float crowdSeparationWeight;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        UBlackboardComponent* blackboardq;

    UPROPERTY(VisibleAnywhere)
        UHICrowdFollowingComponent* crowdFollowingComponent;

protected:

private:

public:

protected:
    virtual void BeginPlay() override;

private:

};

// Created By pablo
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HIPatrol.h"
#include "../MapLogic/HIObjectPooler_Actors.h"
#include "HIMasterSecurity.generated.h"

UCLASS()
class HOWLOFIRON_API AHIMasterSecurity : public AActor
{
    GENERATED_BODY()

public:
    AHIMasterSecurity();
    ~AHIMasterSecurity() { UE_LOG(LogTemp, Log, TEXT("MasterSecurity script deleted.")); }

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        AHIObjectPooler_Actors* objectPooler;

    UPROPERTY()
        TArray<UClass*> TypesOfEnemies;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
        UDataTable* datatable;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
        UDataTable* defaultDatatableOfPatrol;

    UPROPERTY()
        float frequencyShootbase;

    UPROPERTY()
        float combatSeparation;

    UPROPERTY(VisibleAnywhere)
        TArray<AHIPatrol*> patrols;

    UPROPERTY(EditAnywhere)
        TArray<FHI_Patrols> listOfPatrols;

protected:


private:
    UPROPERTY()
        class UPatrolPointsGraph* patrolPointsGraph;

    int patrolsInCombat;

public:
    AHIPatrolPoint* HIGetMinimumPathPatrolPoint(AHIPatrolPoint* initialPatrolPoint, AHIPatrolPoint* targetPatrolPoint);

    UFUNCTION()
        AActor* SpawnEnemies(TSubclassOf<AActor> actorClass);

    UFUNCTION()
        void HIIncrementPatrolsInCombat();

    UFUNCTION()
        void HIDecrementPatrolsInCombat();

    UFUNCTION()
        const int HIGetPatrolsInCombat() const;

protected:

    virtual void BeginPlay() override;
    //virtual void Tick(float DeltaTime) override;

private:

    UFUNCTION()
        void HIInitializePatrolPointsGraph();

    UFUNCTION()
        void FillPatrols();

};

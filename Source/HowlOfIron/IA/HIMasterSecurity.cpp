// Fill out your copyright notice in the Description page of Project Settings.


#include "HIMasterSecurity.h"
#include "Characters/Enemies/HIAlarm.h"
#include "Characters/Enemies/HIEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Game/HIGameData.h"
#include "Game/Patrol/PatrolPointsGraph.h"
#include "HI_DT_MasSec.h"
#include "HIMacros.h"
#include "Kismet/GameplayStatics.h"
#include "HI_DT_Patrol.h"

AHIMasterSecurity::AHIMasterSecurity() :
    datatable(nullptr),
    defaultDatatableOfPatrol(nullptr),
    frequencyShootbase(false),
    objectPooler(nullptr),
    combatSeparation(false),
    patrolPointsGraph(nullptr),
    patrolsInCombat(0)
{
    PrimaryActorTick.bCanEverTick = false;
}

AHIPatrolPoint* AHIMasterSecurity::HIGetMinimumPathPatrolPoint(AHIPatrolPoint* initialPatrolPoint, AHIPatrolPoint* targetPatrolPoint)
{
    return patrolPointsGraph->HIGetMinimumPathPatrolPoint(initialPatrolPoint, targetPatrolPoint);
}

// Called when the game starts or when spawned
void AHIMasterSecurity::BeginPlay()
{
    Super::BeginPlay();

    patrolsInCombat = 0;

    if (datatable)
    {
        FString ContextString = TEXT("Data table context");
        FHI_DT_MasSec* Row = nullptr;
        TArray<FName> RowNames = datatable->GetRowNames();

        Row = datatable->FindRow<FHI_DT_MasSec>(RowNames[0], ContextString, true);
        TypesOfEnemies = Row->TypesOfEnemies;
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("No Datatable MasterSecu."));
    }

    if (defaultDatatableOfPatrol)
    {
        FString ContextString = TEXT("Data table context");
        FHI_DT_Patrol* Row = nullptr;
        TArray<FName> RowNames = defaultDatatableOfPatrol->GetRowNames();

        Row = defaultDatatableOfPatrol->FindRow<FHI_DT_Patrol>(RowNames[0], ContextString, true);

        UHIGameData::HISetMaxEnemiesFirstRing(Row->maxEnemiesFirstRing);
        UHIGameData::HISetMaxEnemiesSecondRing(Row->maxEnemiesSecondRing);
    }


    objectPooler = AHIObjectPooler_Actors::HIGetObjectPooler(GetWorld());

    HIInitializePatrolPointsGraph();

    if (patrols.Num() > 0)
    {
        patrols.Empty();
    }

    int list = listOfPatrols.Num();

    for (int i = 0; i < list; ++i)
    {
        FActorSpawnParameters paramet;
        //paramet.OverrideLevel = this->GetLevel();
        paramet.Owner = this;
        AActor* object = GetWorld()->SpawnActor<AActor>(AHIPatrol::StaticClass(), FVector(0, 0, 10000), FRotator(0), paramet);
        AHIPatrol* patObject = Cast<AHIPatrol>(object);

        UDataTable* patrolDatatable = listOfPatrols[i].patrolDatatable;
        if (patrolDatatable == nullptr)
        {
            patrolDatatable = defaultDatatableOfPatrol;
        }
        patObject->datatable = patrolDatatable;
        patObject->HILoadDatatable(listOfPatrols[i].PatrolDatatbleRow);
        patObject->HISetRoutes(listOfPatrols[i].routes);
        patObject->SetActorEnableCollision(false);
        patObject->HISetMasterSecurity(this);
        patrols.Add(patObject);
    }


    if (objectPooler && patrols.Num() > 0)
    {
        FillPatrols();
    }

    UHIGameData::HIAddMasterSecurity(this);
}

void AHIMasterSecurity::HIInitializePatrolPointsGraph()
{
    TArray<AHIPatrolPoint*> pendentPatrolPoints;
    TArray<AHIPatrolPoint*> visitedPatrolPoints;

#if WITH_EDITOR
    int i = 0;
    int j = 0;
    int k = 0;
    for (FHI_Patrols patrol : listOfPatrols)
    {
        for (FHI_VigilanceRoute route : patrol.routes)
        {
            for (AHIPatrolPoint* patrolPoint : route.targetPoints)
            {

                if (pendentPatrolPoints.Contains(patrolPoint) == false)
                {
                    ensureMsgf(patrolPoint, TEXT("Patrol point in master security is null: %d patrol point in %d route in %d patrol"), i, j, k);
                    pendentPatrolPoints.Add(patrolPoint);
                }

                for (AHIPatrolPoint* neighbour : patrolPoint->HIGetNeighbours())
                {
                    ensureMsgf(neighbour, TEXT("Patrol point has a nullptr neighbour: %d patrol point in %d route in %d patrol"), i, j, k);
                }

                ++i;
            }

            ++j;
        }

        ++k;
    }
#endif

    for (FHI_Patrols patrol : listOfPatrols)
    {
        for (FHI_VigilanceRoute route : patrol.routes)
        {
            for (AHIPatrolPoint* patrolPoint : route.targetPoints)
            {

                if (pendentPatrolPoints.Contains(patrolPoint) == false)
                {
                    ensure(patrolPoint);
                    pendentPatrolPoints.Add(patrolPoint);
                }
            }
        }
    }

    while (pendentPatrolPoints.Num() > 0) {
        AHIPatrolPoint* pathPatrolPoint = pendentPatrolPoints.Pop();
        if (pathPatrolPoint)
        {
            for (AHIPatrolPoint* neighbour : pathPatrolPoint->HIGetNeighbours())
            {
                if (visitedPatrolPoints.Contains(neighbour) == false)
                {
                    pendentPatrolPoints.Add(neighbour);
                }
            }
        }

        visitedPatrolPoints.Add(pathPatrolPoint);
    }


    patrolPointsGraph = NewObject<UPatrolPointsGraph>();
    patrolPointsGraph->HIInitializePatrolPoints(visitedPatrolPoints);
}

AActor* AHIMasterSecurity::SpawnEnemies(TSubclassOf<AActor> actorClass)
{
    AActor* enemy = objectPooler->GetObjectFromPool(actorClass, this);

    return enemy;
}

void AHIMasterSecurity::HIIncrementPatrolsInCombat()
{
    ++patrolsInCombat;
}

void AHIMasterSecurity::HIDecrementPatrolsInCombat()
{
    --patrolsInCombat;
}

const int AHIMasterSecurity::HIGetPatrolsInCombat() const
{
    return patrolsInCombat;
}

void AHIMasterSecurity::FillPatrols()
{
    int32 nPatrols = patrols.Num();

    for (int i = 0; i < nPatrols; ++i)
    {
        AHIPatrol* patrol = patrols[i];

        if (patrol->patrolMembers.Num() > 0)
        {
            patrol->patrolMembers.Empty();
        }

        for (int j = 0; j < patrol->routes.Num(); ++j)
        {
            AHIEnemy* enemy = Cast<AHIEnemy>(SpawnEnemies(patrol->routes[patrol->routes.Num() - 1 - j].spawnedActor));

            //Set enemy voice line
            enemy->voiceNameType = patrol->routes[patrol->routes.Num() - 1 - j].voiceNameType;
            if (enemy->voiceNameType == INVALID)
            {
                enemy->voiceNameType = VoiceDatatableNamesType(FMath::RandRange(1, NUM_NAME_TYPES));
            }

            enemy->patrolReference = patrol;
            enemy->dataTableRow = 0;
            enemy->masterSecurity = this;
            patrol->HIAddEnemyToPatrol(enemy);

            AHIPatrolPoint* spawnPoint = patrol->HIGetEnemyPatrol(enemy).targetPoints[0];
            objectPooler->AddController(enemy);
            float halfCapsule = enemy->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
            FVector spawnPointLocation = spawnPoint->GetActorLocation();
            spawnPointLocation.Z += halfCapsule;
            objectPooler->spawnItem(enemy, spawnPointLocation);
            enemy->SetActorRotation(spawnPoint->GetActorRotation());

            enemy->targetWaypointIndex = 0;
            enemy->currentWaypoint = patrol->HIGetEnemyPatrol(enemy).targetPoints[0];

            // Add alarm if it's white mutton
            UAbilitySystemComponent* enemyAbilitySystem = enemy->GetAbilitySystemComponent();
            FGameplayTagContainer enemyTags;
            enemyAbilitySystem->GetOwnedGameplayTags(enemyTags);
            if (enemyTags.HasTag(GET_GAMEPLAY_TAG(WHITE_MUTTON_TAG)))
            {
                ensureMsgf(enemy->alarmBP, TEXT("Alarm blueprint (alarmBP) not assigned in BP_WhiteMutton"));
				FActorSpawnParameters spawnParameters;
				spawnParameters.Owner = enemy;
                AHIAlarm* alarm = GetWorld()->SpawnActor<AHIAlarm>(enemy->alarmBP, enemy->GetActorLocation(), enemy->GetActorRotation(), spawnParameters);
                if (alarm)
                {
                    alarm->HIAttachAccessoryToSocket(enemy->GetMesh());
                    enemy->HIAddAccessory(alarm);
                    patrol->HIAddAlarm(alarm);
                    alarm->alarmReinforcements = patrol->HIGetEnemyPatrol(enemy).reinforcements;
                }
            }
        }

    }
}



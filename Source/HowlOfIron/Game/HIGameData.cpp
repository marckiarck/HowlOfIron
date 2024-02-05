#include "HIGameData.h"
#include "HIMacros.h"
#include "Characters/Enemies/HI_DT_EnemyAccessory.h"
#include "Characters/VincentVolk/HIWerewolf.h"
#include "IA/HIMasterSecurity.h"
#include "Characters/VincentVolk/HIWerewolfController.h"
#include "Kismet/GameplayStatics.h"

float UHIGameData::frequencyShoot = 0.f;
float UHIGameData::dodgeProbability = 0.f;

AHIWerewolf* UHIGameData::playerWerewolf = nullptr;
AHIWerewolfController* UHIGameData::playerController = nullptr;
AHICameraManager* UHIGameData::cameraManager = nullptr;

//enemies
TArray<AHIMasterSecurity*> UHIGameData::masterSecuritiesArray;
TArray<AHIEnemy*> UHIGameData::enemiesArray;
TArray<AHIEnemy*> UHIGameData::enemiesCombatArray;
TArray<AHIEnemy*> UHIGameData::enemiesFirstRingArray;
TArray<AHIEnemy*> UHIGameData::enemiesSecondRingArray;
TArray<AHIEnemy*> UHIGameData::enemiesThirdRingArray;
int UHIGameData::maxEnemiesFirstRing = 0;
int UHIGameData::maxEnemiesSecondRing = 0;
FVector UHIGameData::werewolfEQSPosition = FVector(0.f);
FVector UHIGameData::steamPosition = FVector(0.f);


UHIGameOverworldDirector* UHIGameData::gameManager = nullptr;
AHIAmbientSound* UHIGameData::speaker2D = nullptr;
bool UHIGameData::debugMode = false;
UDataTable* UHIGameData::enemyAccessoriesDatatable = nullptr;
UGameplayEffect* UHIGameData::staticGameplayEffect = nullptr;

AHIEnemy* UHIGameData::boss = nullptr;

AHITeleportPawn* UHIGameData::teleportPawn = nullptr;

UHIGameInstance* UHIGameData::gameInstance = nullptr;

AHIWerewolf* UHIGameData::HIGetPlayerWerewolf()
{
    return playerWerewolf;
}

void UHIGameData::HISetPlayerWerewolf(AHIWerewolf* newPlayerWerewolf)
{
    playerWerewolf = newPlayerWerewolf;
}

void UHIGameData::HIAddMasterSecurity(AHIMasterSecurity* _masterSecurity)
{
    masterSecuritiesArray.Add(_masterSecurity);
}

void UHIGameData::HIRemoveMasterSecurity(AHIMasterSecurity* _masterSecurity)
{
    masterSecuritiesArray.Remove(_masterSecurity);
}

AHICameraManager* UHIGameData::HIGetCameraManager()
{
    return cameraManager;
}

void UHIGameData::HISetCameraManager(AHICameraManager* _cameraManager)
{
    cameraManager = _cameraManager;
}



void UHIGameData::HISetMaxEnemiesFirstRing(int _num)
{
    maxEnemiesFirstRing = _num;
    //enemiesFirstRingArray.SetNumUninitialized();

}

int UHIGameData::HIGetMaxEnemiesFirstRing()
{
    return maxEnemiesFirstRing;
}

void UHIGameData::HISetMaxEnemiesSecondRing(int _num)
{
    maxEnemiesSecondRing = _num;
}

int UHIGameData::HIGetMaxEnemiesSecondRing()
{
    return maxEnemiesSecondRing;
}

TArray<AHIEnemy*> UHIGameData::HIGetEnemiesArray()
{
    return enemiesArray;
}

void UHIGameData::HIAddEnemyToArray(AHIEnemy* _enemy)
{
    if (enemiesArray.Find(_enemy) == INDEX_NONE)
    {
        enemiesArray.Add(_enemy);
    }

}


void UHIGameData::HIRemoveEnemyFromArray(AHIEnemy* _enemy)
{
    enemiesArray.Remove(_enemy);
}


TArray<AHIEnemy*> UHIGameData::HIGetCombatEnemiesArray()
{
    return enemiesCombatArray;
}

void UHIGameData::HIAddEnemyToCombatArray(AHIEnemy* _enemy)
{
    if (enemiesCombatArray.Find(_enemy) == INDEX_NONE)
    {
        enemiesCombatArray.Add(_enemy);
    }
}

void UHIGameData::HIRemoveEnemyFromCombatArray(AHIEnemy* _enemy)
{
    enemiesCombatArray.Remove(_enemy);
}

TArray<AHIEnemy*> UHIGameData::HIGetEnemiesFirstRingArray()
{
    return enemiesFirstRingArray;
}

void UHIGameData::HIAddEnemyToFirstArray(AHIEnemy* _enemy)
{
    if (enemiesFirstRingArray.Find(_enemy) == INDEX_NONE)
    {
        enemiesFirstRingArray.Add(_enemy);
    }
}

void UHIGameData::HIRemoveEnemyFromFirstArray(AHIEnemy* _enemy)
{
    if (enemiesFirstRingArray.Find(_enemy) != INDEX_NONE)
    {
        enemiesFirstRingArray.Remove(_enemy);
    }
}

TArray<AHIEnemy*> UHIGameData::HIGetEnemiesSecondRingArray()
{
    return enemiesSecondRingArray;
}

void UHIGameData::HIAddEnemyToSecondArray(AHIEnemy* _enemy)
{
    if (enemiesSecondRingArray.Find(_enemy) == INDEX_NONE)
    {
        enemiesSecondRingArray.Add(_enemy);
    }
}

void UHIGameData::HIRemoveEnemyFromSecondArray(AHIEnemy* _enemy)
{
    if (enemiesSecondRingArray.Find(_enemy) != INDEX_NONE)
    {
        enemiesSecondRingArray.Remove(_enemy);
    }
}

TArray<AHIEnemy*> UHIGameData::HIGetEnemiesThirdRingArray()
{
    return enemiesThirdRingArray;
}

void UHIGameData::HIAddEnemyToThirdArray(AHIEnemy* _enemy)
{
    if (enemiesThirdRingArray.Find(_enemy) == INDEX_NONE)
    {
        enemiesThirdRingArray.Add(_enemy);
    }
}

void UHIGameData::HIRemoveEnemyFromThirdArray(AHIEnemy* _enemy)
{
    if (enemiesThirdRingArray.Find(_enemy) != INDEX_NONE)
    {
        enemiesThirdRingArray.Remove(_enemy);
    }
}

FVector UHIGameData::HIGetWerewolfEQSPosition()
{
    return werewolfEQSPosition;
}

void UHIGameData::HISetWerewolfEQSPosition(FVector _newPos)
{
    werewolfEQSPosition = _newPos;
}

AHIAmbientSound* UHIGameData::HIGetSpeaker2D()
{
    return speaker2D;
}

void UHIGameData::HISetSpeaker(AHIAmbientSound* _speaker)
{
    speaker2D = _speaker;
}

UHIGameOverworldDirector* UHIGameData::HIGetGameManager()
{
    return gameManager;
}

void UHIGameData::HISetGameManager(UHIGameOverworldDirector* _gameManager)
{
    gameManager = _gameManager;
}

UGameplayEffect* UHIGameData::HIGetStaticGameplayEffect()
{
    return staticGameplayEffect;
}

void UHIGameData::HISetStaticEffect(UGameplayEffect* _effect)
{
    staticGameplayEffect = _effect;
}

FGameplayTag UHIGameData::HICheckClass(FGameplayTagContainer _containertoCheck)
{
    TArray<FGameplayTag>::TConstIterator iter = _containertoCheck.CreateConstIterator();

    //     for (FGameplayTag tagname : iter)
    //     {
    //         if (_tagsclass.HasTagExact(tagname))
    //         {
    //             return tagname;
    //         }
    //     }


    FGameplayTagContainer refclasscontainer;
    GET_ENEMY_TAGS(refclasscontainer);

    for (iter; iter; ++iter)
    {
        if (refclasscontainer.HasTagExact(*iter))
        {
            return *(iter);
        }
    }

    return FGameplayTag();
}

void UHIGameData::HISetSteamPosition(FVector _pos)
{
steamPosition = _pos;
}

FVector UHIGameData::HIGetSteamPosition()
{
return steamPosition;
}

class UWorld* UHIGameData::HIGetWerewolfWorld()
{
    if (playerWerewolf && playerWerewolf->IsValidLowLevel())
    {
        return playerWerewolf->GetWorld();
    }

    return nullptr;
}

FVector UHIGameData::HIGetWerewolfLocation()
{
    FVector werewolfLocation = FVector::ZeroVector;
    if (playerWerewolf)
    {
        werewolfLocation = playerWerewolf->GetActorLocation();
    }
    return werewolfLocation;
}

void UHIGameData::HIDebugModeToggle()
{
    if (debugMode)
    {
        debugMode = false;
    }
    else
    {
        debugMode = true;
    }
}

bool UHIGameData::HIGetDebugMode()
{
    return debugMode;
}

bool UHIGameData::HIInCombat()
{
    for (AHIMasterSecurity* masterSecurityIter : masterSecuritiesArray)
    {
        if (masterSecurityIter->HIGetPatrolsInCombat() != 0)
        {
            

            return true;
        }
    }

    return false;
}

UDataTable* UHIGameData::HIGetEnemyAccessoriesDatatable()
{
    return enemyAccessoriesDatatable;
}

void UHIGameData::HISetEnemyAccessoriesDatatable(UDataTable* _enemyAccessoriesDatatable)
{
    enemyAccessoriesDatatable = _enemyAccessoriesDatatable;
}

TArray<FName> UHIGameData::HIGetEnemyAccessoriesRowNames()
{
    TArray<FName> accessoriesRowNames;
    if (enemyAccessoriesDatatable)
    {
        accessoriesRowNames = enemyAccessoriesDatatable->GetRowNames();
    }
    return accessoriesRowNames;
}

int32 UHIGameData::HIGetEnemyAccessoryIDByName(FName _accessoryName)
{
    if (enemyAccessoriesDatatable)
    {
        FString ContextString = TEXT("Data table context");
        FHI_DT_EnemyAccessory* Row = nullptr;
        TArray<FName> RowNames = enemyAccessoriesDatatable->GetRowNames();

        Row = enemyAccessoriesDatatable->FindRow<FHI_DT_EnemyAccessory>(_accessoryName, ContextString, true);
        if (Row)
        {
            return Row->accessoryID;
        }
    }
    return -1;
}

FGameplayTagContainer UHIGameData::HIGetCombatTags()
{
    FGameplayTagContainer combatTags;

    combatTags.AddTag(GET_GAMEPLAY_TAG(COMBAT_SHOOT_TAG));
    combatTags.AddTag(GET_GAMEPLAY_TAG(COMBAT_MOVE_TAG));
    combatTags.AddTag(GET_GAMEPLAY_TAG(COMBAT_ALARM_TAG));
    combatTags.AddTag(GET_GAMEPLAY_TAG(ALERT_TO_PATROL_TAG));
    return combatTags;
}

void UHIGameData::HIPauseEnemies()
{
    for (AHIEnemy* enemyIter : enemiesArray)
    {
        enemyIter->GetAbilitySystemComponent()->AddLooseGameplayTag(GET_GAMEPLAY_TAG(STOP_BT_TAG));
    }
}

void UHIGameData::HIResumeEnemies()
{
    for (AHIEnemy* enemyIter : enemiesArray)
    {
        enemyIter->GetAbilitySystemComponent()->RemoveLooseGameplayTag(GET_GAMEPLAY_TAG(STOP_BT_TAG));
    }
}

void UHIGameData::HIClearStaticReferences()
{

    playerWerewolf = nullptr;
    masterSecuritiesArray.Empty();
    cameraManager = nullptr;
    gameManager = nullptr;
    //speaker2D = nullptr;
    enemyAccessoriesDatatable = nullptr;
    staticGameplayEffect = nullptr;

    enemiesArray.Empty();
    enemiesCombatArray.Empty();
    enemiesFirstRingArray.Empty();
    enemiesSecondRingArray.Empty();
    enemiesThirdRingArray.Empty();
 

}

bool UHIGameData::IsWithEditor()
{

//return true;

#if WITH_EDITOR
    return true;
#else
    return false;
#endif
}

bool UHIGameData::HIIsPositionOnScreen(FVector _position, FVector2D& outRelativeScreenPos_, float& outRotationAngle_)
{
    FVector2D screenSize = FVector2D(0.f, 0.f);
    FVector2D screenPos = FVector2D(0.f, 0.f);
    //ensureMsgf(playerWerewolf, TEXT("PlayerWerewolf is null"));
    if (!playerWerewolf)
    {
        return false;
    }
    playerWerewolf->GetWorld()->GetGameViewport()->GetViewportSize(screenSize);
    //ensureMsgf(playerWerewolf->GetController<APlayerController>(), TEXT("Werewolf controller is null"));
    if (!playerWerewolf->GetController<APlayerController>())
    {
        return false;
    }
    playerWerewolf->GetController<APlayerController>()->ProjectWorldLocationToScreen(_position, screenPos);

    if (screenPos.X > 0.f && screenPos.X < screenSize.X &&
        screenPos.Y > 0.f && screenPos.Y < screenSize.Y)
    {
        return true;
    }

    FVector2D screenCenter = FVector2D(screenSize.X / 2, screenSize.Y / 2);

    screenPos -= screenCenter;

    float angleRadians = FMath::Atan2(screenPos.Y, screenPos.X);
    angleRadians -= FMath::DegreesToRadians(90.f);

    outRotationAngle_ = FMath::RadiansToDegrees(angleRadians) + 180.f;

    float cos = cosf(angleRadians);
    float sin = -sinf(angleRadians);

    screenPos = FVector2D(screenCenter.X + (sin * 150.f), screenCenter.Y + cos * 150.f);

    float m = cos / sin;

    FVector2D screenBounds = screenCenter;

    if (cos > 0)
    {
        screenPos = FVector2D(screenBounds.Y / m, screenBounds.Y);
    }
    else
    {
        screenPos = FVector2D(-screenBounds.Y / m, -screenBounds.Y);
    }

    if (screenPos.X > screenBounds.X)
    {
        screenPos = FVector2D(screenBounds.X, screenBounds.X * m);
    }
    else if (screenPos.X < -screenBounds.X)
    {
        screenPos = FVector2D(-screenBounds.X, -screenBounds.X * m);
    }

    screenPos += screenCenter;

    outRelativeScreenPos_ = screenPos / screenSize; // Relative to screenSize

    return false;
}

bool UHIGameData::HIIsPositionOnScreen(FVector _position)
{
    FVector2D outScreenPos;
    float outRotationAngle = 0.f;
    return HIIsPositionOnScreen(_position, outScreenPos, outRotationAngle);
}

float UHIGameData::HIGetDodgePorbability()
{
    return dodgeProbability;
}

float UHIGameData::HIGetFrecuencyShoot()
{
    return frequencyShoot;
}

void UHIGameData::HISetBoss(AHIEnemy* enemy)
{
    if (enemy)
    {
        bool isBoss = false;
        CHECK_HAS_TAG(enemy->GetAbilitySystemComponent(), BOSS_TAG, isBoss);

        if (isBoss)
        {
            boss = enemy;
        }
    }
}

AHIEnemy* UHIGameData::HIGetBoss()
{
    return boss;
}

void UHIGameData::HISetTeleportPawn(AHITeleportPawn* _teleportPawn)
{
    teleportPawn = _teleportPawn;
}

AHITeleportPawn* UHIGameData::HIGetTeleportPawn()
{
    return teleportPawn;
}

void UHIGameData::HISetGameInstance(UHIGameInstance* newGameInstance)
{
    gameInstance = newGameInstance;
}

UHIGameInstance* UHIGameData::HIGetGameInstance()
{
    return gameInstance;
}

void UHIGameData::HIShowTooltip(FName RowName)
{
    if (gameInstance)
    {
        gameInstance->HIShowTooltip(RowName);
    }
}

AHIWerewolfController* UHIGameData::HIGetPlayerController()
{
    return playerController;
}

void UHIGameData::HISetPlayerController(AHIWerewolfController* _playerController)
{
    playerController = _playerController;
}

float UHIGameData::HIGetFPS()
{
    return playerController->HIGetFPS();
}

void  UHIGameData::HIKillEnemies()
{
    for (AHIEnemy* enemy : enemiesArray)
    {
        AHIObjectPooler_Actors::HIGetObjectPooler()->DespawnItem(enemy);
    }
}

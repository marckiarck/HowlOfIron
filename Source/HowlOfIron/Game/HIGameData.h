#pragma once
#include "CoreMinimal.h"
#include "MapLogic/HIGameOverworldDirector.h"
#include "HIGameInstance.h"
#include "HIGameData.generated.h"

//Generic delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGenericEvent);

//Author @all

class AHIWerewolf;
class AHIMasterSecurity;
class AHICameraManager;
class AHIWerewolfController;

UCLASS(BlueprintType, Blueprintable)
class HOWLOFIRON_API UHIGameData : public UObject
{

    GENERATED_BODY()

public:
    static UPROPERTY(BlueprintReadOnly) float frequencyShoot;
    static UPROPERTY(BlueprintReadOnly) float dodgeProbability;

private:
    static UPROPERTY(Transient) AHIWerewolf* playerWerewolf;
    static UPROPERTY(Transient) AHIWerewolfController* playerController;
    static UPROPERTY(Transient) AHICameraManager* cameraManager;

    //enemies
    static UPROPERTY(Transient) TArray<AHIMasterSecurity*> masterSecuritiesArray;
    static UPROPERTY(Transient) TArray<AHIEnemy*> enemiesArray;
    static UPROPERTY(Transient) TArray<AHIEnemy*> enemiesCombatArray;
    static UPROPERTY(Transient) TArray<AHIEnemy*> enemiesFirstRingArray;
    static UPROPERTY(Transient) TArray<AHIEnemy*> enemiesSecondRingArray;
    static UPROPERTY(Transient) TArray<AHIEnemy*> enemiesThirdRingArray;

    static UPROPERTY() int maxEnemiesFirstRing;
    static UPROPERTY() int maxEnemiesSecondRing;
    static UPROPERTY() FVector werewolfEQSPosition;
    static UPROPERTY() FVector steamPosition;


    static UPROPERTY(Transient) UHIGameOverworldDirector* gameManager;
    static UPROPERTY(Transient) AHIAmbientSound* speaker2D;
    static UPROPERTY(Transient) UDataTable* enemyAccessoriesDatatable;

    //Don't use
    static UPROPERTY(Transient) UGameplayEffect* staticGameplayEffect;

    static UPROPERTY(Transient) AHIEnemy* boss;

    static UPROPERTY(Transient) AHITeleportPawn* teleportPawn;

    static UPROPERTY(Transient) UHIGameInstance* gameInstance;

    static bool  debugMode;

public:

    UFUNCTION(BlueprintCallable)
        static AHIWerewolf* HIGetPlayerWerewolf();
    static void HISetPlayerWerewolf(AHIWerewolf* newPlayerWerewolf);


    UFUNCTION()
        static void HIAddMasterSecurity(AHIMasterSecurity* _masterSecurity);
    static void HIRemoveMasterSecurity(AHIMasterSecurity* _masterSecurity);

    UFUNCTION(BlueprintCallable)
        static AHICameraManager* HIGetCameraManager();

    static void HISetCameraManager(AHICameraManager* _cameraManager);


    //Enemies Functions

    UFUNCTION(BlueprintCallable)
        static void HISetMaxEnemiesFirstRing(int _num);
    UFUNCTION(BlueprintCallable)
        static int HIGetMaxEnemiesFirstRing();


    UFUNCTION(BlueprintCallable)
        static void HISetMaxEnemiesSecondRing(int _num);

    UFUNCTION(BlueprintCallable)
        static int HIGetMaxEnemiesSecondRing();

    UFUNCTION(BlueprintCallable)
        static TArray<AHIEnemy*> HIGetEnemiesArray();

    UFUNCTION(BlueprintCallable)
        static void HIAddEnemyToArray(AHIEnemy* _enemy);

    static void HIRemoveEnemyFromArray(AHIEnemy* _enemy);

    //Combat Enemies
    UFUNCTION(BlueprintCallable)
        static TArray<AHIEnemy*> HIGetCombatEnemiesArray();

    UFUNCTION(BlueprintCallable)
        static void HIAddEnemyToCombatArray(AHIEnemy* _enemy);

    static void HIRemoveEnemyFromCombatArray(AHIEnemy* _enemy);



    UFUNCTION(BlueprintCallable)
        static TArray<AHIEnemy*> HIGetEnemiesFirstRingArray();

    UFUNCTION(BlueprintCallable)
        static void HIAddEnemyToFirstArray(AHIEnemy* _enemy);
    UFUNCTION(BlueprintCallable)
        static void HIRemoveEnemyFromFirstArray(AHIEnemy* _enemy);


    UFUNCTION(BlueprintCallable)
        static TArray<AHIEnemy*> HIGetEnemiesSecondRingArray();

    UFUNCTION(BlueprintCallable)
        static void HIAddEnemyToSecondArray(AHIEnemy* _enemy);
    UFUNCTION(BlueprintCallable)
        static void HIRemoveEnemyFromSecondArray(AHIEnemy* _enemy);


    UFUNCTION(BlueprintCallable)
        static TArray<AHIEnemy*> HIGetEnemiesThirdRingArray();

    UFUNCTION(BlueprintCallable)
        static void HIAddEnemyToThirdArray(AHIEnemy* _enemy);
    UFUNCTION(BlueprintCallable)
        static void HIRemoveEnemyFromThirdArray(AHIEnemy* _enemy);


    UFUNCTION(BlueprintCallable)
        static FVector HIGetWerewolfEQSPosition();

    UFUNCTION(BlueprintCallable)
        static void HISetWerewolfEQSPosition(FVector _newPos);



    UFUNCTION(BlueprintCallable)
        static AHIAmbientSound* HIGetSpeaker2D();
    static void HISetSpeaker(AHIAmbientSound* _speaker);

    UFUNCTION(BlueprintCallable)
        static UHIGameOverworldDirector* HIGetGameManager();
    static void HISetGameManager(UHIGameOverworldDirector* _gameManager);


    UFUNCTION(BlueprintCallable)
        static UGameplayEffect* HIGetStaticGameplayEffect();

    static void HISetStaticEffect(UGameplayEffect* _effect);

    UFUNCTION(BlueprintCallable)
        static FGameplayTag HICheckClass(FGameplayTagContainer _containertoCheck);

    UFUNCTION(BlueprintCallable)
        static void HISetSteamPosition(FVector _pos);

    UFUNCTION(BlueprintCallable)
        static FVector HIGetSteamPosition();

    UFUNCTION(BlueprintCallable)
        static class UWorld* HIGetWerewolfWorld();

    UFUNCTION(BlueprintCallable)
        static FVector HIGetWerewolfLocation();

    static void HIDebugModeToggle();

    UFUNCTION(BlueprintCallable)
        static bool HIGetDebugMode();

    UFUNCTION(BlueprintCallable)
        static bool HIInCombat();

    UFUNCTION(BlueprintCallable)
        static UDataTable* HIGetEnemyAccessoriesDatatable();
    static void HISetEnemyAccessoriesDatatable(UDataTable* _enemyAccessoriesDatatable);
    static TArray<FName> HIGetEnemyAccessoriesRowNames();
    static int32 HIGetEnemyAccessoryIDByName(FName _accessoryName);


    UFUNCTION(BlueprintCallable)
        static FGameplayTagContainer HIGetCombatTags();

    /// <summary>
    /// Pause enemies behaviourTrees
    /// </summary>
    UFUNCTION(BlueprintCallable)
        static void HIPauseEnemies();

    /// <summary>
    /// Resume enemies behaviourTrees
    /// </summary>
    UFUNCTION(BlueprintCallable)
        static void HIResumeEnemies();

    UFUNCTION(BlueprintCallable)
        static void HIClearStaticReferences();

    /// <summary>
    /// Return boolean <true> when playing on editor and <false> when not.
    /// </summary>
    UFUNCTION(BlueprintPure)
        static bool IsWithEditor();

    /// <summary>
    ///		Checks if the _position is on screen
    /// </summary>
    /// <param name="_position">position to check</param>
    /// <param name="outRelativeScreenPos_">screen relative pos for marking. This value is in the range [0, 1]</param>
    /// <param name="outRotationAngle_">angle rotation for marking</param>
    /// <returns>
    ///		- true if _position is on screen
    ///		- false if not
    /// </returns>
    static bool HIIsPositionOnScreen(FVector _position, FVector2D& outRelativeScreenPos_, float& outRotationAngle_);
    static bool HIIsPositionOnScreen(FVector _position);

    UFUNCTION(BlueprintPure)
        static float HIGetDodgePorbability();

    UFUNCTION(BlueprintPure)
        static float HIGetFrecuencyShoot();

    UFUNCTION()
        static void HISetBoss(AHIEnemy* enemy);

    static AHIEnemy* HIGetBoss();

    UFUNCTION()
        static void HISetTeleportPawn(AHITeleportPawn* _teleportPawn);

    UFUNCTION(BlueprintCallable)
	    static AHITeleportPawn* HIGetTeleportPawn();

	UFUNCTION()
		static void HISetGameInstance(UHIGameInstance* newGameInstance);

    UFUNCTION(BlueprintCallable)
    static UHIGameInstance* HIGetGameInstance();

    UFUNCTION(BlueprintCallable)
    static void HIShowTooltip(FName rowName);
    
UFUNCTION(BlueprintCallable)
        static AHIWerewolfController* HIGetPlayerController();

    UFUNCTION()
        static void HISetPlayerController(AHIWerewolfController* _playerController);
            
    UFUNCTION(BlueprintCallable)
        static float HIGetFPS();

    UFUNCTION(BlueprintCallable)
    static void HIKillEnemies();
};

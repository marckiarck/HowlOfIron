// Created by pablo

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Components/WidgetComponent.h"
#include "UI/HIEnemyHUD.h"
#include "PhysicsEngine/PhysicalAnimationComponent.h"
#include "Characters/Enemies/HIEnemiesAttributes.h"
#include "../HIAbilityCharacter.h"
#include <Game/Patrol/HIPatrolPoint.h>
#include "Game/PerceptionSystem/HIDetectorActorComponent.h"
#include "GameplayTagContainer.h"
#include "../../MapLogic/HI_Requisit.h"
#include "HIEnemyAccessoryStruct.h"
#include "ExecutionPoints/HIExecutionPointComponent.h"
#include <HIMacros.h>
#include "UI/HITargetEnemyHUD.h"
#include "HIEnemy.generated.h"


const float TICKDISTANCE = 9000.f * 9000.f;

const int NUM_NAME_TYPES = 5;
UENUM()
enum VoiceDatatableNamesType {
    Josh = 1,
    Ellis = 2,
    Ivan = 3,
    Diego = 4,
    Guille = 5,
    INVALID = 0
};

UCLASS(BlueprintType, Blueprintable)
class HOWLOFIRON_API AHIEnemy : public AHIAbilityCharacter
{
    GENERATED_BODY()


public:
    AHIEnemy();
    ~AHIEnemy();

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        bool inCombat = false;

    UPROPERTY(BlueprintReadOnly)
        bool movingBack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Accessories)
        UDataTable* accessoriesDataTable;

    /// <summary>
    /// Structs of the accessories
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Accessories)
        TArray<FHIEnemyAccessoryStruct> accessoriesStructs;

    /// <summary>
    /// Accessories of the enemy
    /// </summary>
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Accessories)
        TArray<class AHIEnemyAccessory*> accessories;

    /// <summary>
    /// Weapon carried by the enemy
    /// </summary>
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Accessories)
        class AHIEnemyAccessory* actualWeapon;

    /// <summary>
    /// Previous weapon carried by the enemy (to activate actual and deactivate previous correctly)
    /// </summary>
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Accessories)
        class AHIEnemyAccessory* previousWeapon;

    UPROPERTY(VisibleDefaultsOnly, Category = PhysicsAnimComp)
        UPhysicalAnimationComponent* physicAnimComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = Sound)
        class UAudioComponent* shoutAudioComponent;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "HUD")
        UWidgetComponent* enemyBars;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "HUD")
        UHIEnemyHUD* hudReference;

    UPROPERTY(VisibleDefaultsOnly, Category = "HUD")
        UWidgetComponent* enemyTargetImage;

    UPROPERTY(VisibleDefaultsOnly, Category = "HUD")
        UHITargetEnemyHUD* targetEnemyReference;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System", meta = (RequiredAssetDataTags = "RowStructure=AttributeMetaData"))
        UDataTable* statsDatatable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System|Gameplay Effects")
        TSubclassOf<class UGameplayEffect> stopWhenAttackedEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System")
        FGameplayTagContainer tagtoAddOnStart;


    //Abilities class

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System")
        TArray<TSubclassOf<class UGameplayAbility>> abiliyList;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System|Gameplay Effects")
        TSubclassOf<class UGameplayEffect> changeDetectionMeterEffect;

    UPROPERTY(Transient)
        UGameplayEffect* changeDetectionMeterEffectRef;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System|Gameplay Effects")
        TSubclassOf<class UGameplayEffect> hitOtherMuttonInRagdoll;

    UPROPERTY(Transient)
        UGameplayEffect* hitOtherMuttonInRagdollRef;

    UPROPERTY(Transient)
        UGameplayEffect* DistanceDisableGERef;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        class AHIPatrol* patrolReference;

    UPROPERTY(Transient, BlueprintReadOnly)
        class AHIMasterSecurity* masterSecurity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        MissionReq missionReq;

    UPROPERTY()
        int dataTableRow;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
        UDataTable* datatable;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh Material")
        class UMaterialInstanceDynamic* dynamicMaterial;

    //Route variables
    UPROPERTY()
        int targetWaypointIndex;

    UPROPERTY()
        AHIPatrolPoint* currentWaypoint;

    // Used in HIEnemyService_SearchPlayer
    UPROPERTY()
        bool playerLastSeen;

    UPROPERTY()
        bool enemyHitted = false;

    /// <summary>
    /// Alarm blueprint class from which we are going to create the alarm
    /// </summary>
    UPROPERTY(EditAnywhere, Category = "Alarm", meta = (Tooltip = "(Only neccessary for white muttons)"))
        TSubclassOf<class AHIAlarm> alarmBP = nullptr;

    /// <summary>
    /// Alarm that the enemy will call
    /// </summary>
    UPROPERTY(Transient)
        class AHIAlarm* alarmAssigned = nullptr;

    UPROPERTY(Transient)
        AHIEnemy* enemyToHit;


    UPROPERTY(VisibleAnywhere, Category = "Voice Acting")
        TEnumAsByte<VoiceDatatableNamesType> voiceNameType;

    FGenericEvent OnDeath;

protected:

#pragma region DELEGATES
    FDelegateHandle enemyHealthChangedDelegateHandle;
    FDelegateHandle enemyMaxHealthChangedDelegateHandle;
    FDelegateHandle enemySpeedChangedDelegateHandle;
    FDelegateHandle enemyFearChangedDelegateHandle;
    FDelegateHandle enemyDetectionChangedDelegateHandle;
#pragma endregion


private:
    UPROPERTY(Transient, SkipSerialization)
        const UHIEnemiesAttributes* enemiesAttributes;

    UPROPERTY(VisibleAnywhere, Transient, BlueprintType)
        UHIDetectorActorComponent* detectorComponent;

    UPROPERTY(EditAnywhere, Category = "Ability System")
        FGameplayTag tagClass;

    UPROPERTY(Transient)
        AHIPatrolPoint* arriveWaypoint;

    UPROPERTY()
        float launchGrenadeRadious = 500.f;

    UPROPERTY(EditAnywhere, meta = (DisplayName = "BackExecutionSameLevelPoint"))
        UHIExecutionPointComponent* executionSameLevelPoint;

    UPROPERTY(EditAnywhere, meta = (DisplayName = "BackExecutionTopLevelPoint"))
        UHIExecutionPointComponent* executionTopLevelPoint;

public:
    const UHIEnemiesAttributes* HIGetAttributes() { return enemiesAttributes; }

    UFUNCTION()
        /// <summary>
        /// returns the position of the patrol waypoint where the enemy wants to go
        /// </summary>
        /// <returns> patrol destiny </returns>
        FVector HIGetPatrolPosition();

    UFUNCTION()
        FVector HIGetExecutionPosition(bool sameLevelExecution, bool& backExecution);

    UFUNCTION()
        void HICalculateCombatBehaviour();

    UFUNCTION(BlueprintCallable)
        const float HIGetMaxFear() const;

    UFUNCTION(BlueprintCallable)
        const float HIGetFear() const;

    UFUNCTION(BlueprintCallable)
        const float HIGetDetectionValue() const;

    UFUNCTION()
        UHIDetectorActorComponent* HIGetDetectorComponent();

    UFUNCTION(BlueprintCallable)
        void HIChangeDetectionMeter(float _changeValue);

    UFUNCTION()
        AHIPatrolPoint* HIGetTargetPoint();

    UFUNCTION()
        AHIPatrolPoint* HIGetArrivePoint();

    UFUNCTION()
        void HIExitCombat();

    UFUNCTION(BlueprintImplementableEvent)
        void HIGreenDeath();


    UFUNCTION()
        void HISetNormalDetection();

    UFUNCTION(BlueprintCallable)
        const FGameplayTag GetClassTag() const { return tagClass; }

    UFUNCTION()
        void HIUnassignAlarm();

	UFUNCTION(BlueprintCallable)
		bool HIIsbackToWall();

    UFUNCTION()
        void HIAddAccessory(class AHIEnemyAccessory* _accessoryToAdd);

    /// <summary>
    /// Function to change the active weapon (it hides the mesh of the actual weapon and makes visible the other weapon)
    /// </summary>
    /// <parameters>
    /// _weaponIDToChange: weapon ID we want to makes visible
    /// </parameters>
    UFUNCTION(BlueprintCallable)
        void HIChangeWeapon(int32 _weaponIDToChange);

    /// <summary>
    /// Function to get an accessory by id
    /// </summary>
    /// <parameters>
    /// _accessoryID: The id of the accessory
    /// </parameters>
    UFUNCTION()
        AHIEnemyAccessory* HIGetAccessoryByID(int32 _accessoryID) const;

   UFUNCTION(BlueprintCallable)
	   void HITryLaunchGranade(FVector objetivePosition);

   UFUNCTION()
      void HISetVisibility(bool hideBool);

    virtual FString HIGetVoiceString() override;

    virtual void PostInitProperties() override;
#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

    //    UFUNCTION()
    //       void HISetTargetHUDVisibility(ESlateVisibility _visibility);

    UFUNCTION(BlueprintCallable)
        void HISetVulnerability(bool _val);
//     UFUNCTION(BlueprintNativeEvent)
//         void HIInitAtributes();
// 
//     UFUNCTION(BlueprintCallable)


protected:

    virtual void BeginPlay() override;

    void HIAssignCharacterType();

    virtual void Tick(float DeltaTime) override;


#pragma region DELEGATES_FUNCTIONS

    virtual void HIHealthChanged(const FOnAttributeChangeData& Data);
    virtual void HIMaxHealthChanged(const FOnAttributeChangeData& Data);
    virtual void HIspeedChanged(const FOnAttributeChangeData& Data);
    virtual void HIchargedValueChanged(const FOnAttributeChangeData& Data);
    virtual void HIfearArmourChanged(const FOnAttributeChangeData& Data);
    virtual void HIDetectionChanged(const FOnAttributeChangeData& Data);

#pragma endregion

private:

    UFUNCTION()
        void HIActivateDelegates();

    UFUNCTION(BlueprintCallable)
        void HIDeath();

    UFUNCTION()
        void HITurnIntoRagdoll();

    UFUNCTION()
        void HIThrownRagdoll(float _deltaTime);

    UFUNCTION(BlueprintCallable)
        virtual void HINavLinkPosition(FVector _EndPos);

   UFUNCTION()
      bool HICanLaunchGrenade(FVector objetivePosition);

    /// <summary>
    /// Updates the variables used to get the target waypoint to obtain the next waupoint in the patrol
    /// </summary>
    UFUNCTION()
        void HIUpdateTargetWaypoint();

    UFUNCTION()
        TArray<FName> HIGetEnemyAccessoriesRowNames();


    UFUNCTION()
        bool HICheckDistance();

};

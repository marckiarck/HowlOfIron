// @AUTHORS: #ALL
// @AUTHORS: #ALL
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include <GameplayAbilitySpec.h>
#include "CineCameraComponent.h"
#include "PhysicsEngine/PhysicalAnimationComponent.h"
#include "HIWerewolfAbilitiesData.h"
#include "HIWerewolfAttributes.h"
#include "UI/HIVincentHUD.h"
#include "../HIAbilityCharacter.h"
#include "UI/HIButtonHUD.h"
#include "HICineCamera.h"
#include <NiagaraComponent.h>
#include <NiagaraSystem.h>
#include "HIWerewolf.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AHICameraManager;

UCLASS(BlueprintType, Blueprintable)
class HOWLOFIRON_API AHIWerewolf : public AHIAbilityCharacter
{
	GENERATED_BODY()

public:
	AHIWerewolf();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USpringArmComponent* springArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UCineCameraComponent* cineCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UNiagaraComponent* smokesComponentIz;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UNiagaraComponent* smokesComponentDe;

	UPROPERTY(VisibleDefaultsOnly, Category = PhysicsAnimComp)
		UPhysicalAnimationComponent* physicAnimComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* scriptedCameraClass;

	UPROPERTY(Transient)
		AHICineCamera* scriptedCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UMaterialInstance*> materialsForRage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UNiagaraSystem*> smokesForRage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialParameterCollection* effects_Howl_Dash_Claws;



#pragma region GAMEPLAY_ABIILITY_SYSTEM

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System")
		UDataTable* statsDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System", meta = (RequiredAssetDataTags = "RowStructure=AttributeMetaData"))
		UDataTable* abilityDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System")
		TArray<TSubclassOf<class UGameplayAbility>> abiliyList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System")
		const UHIWerewolfAttributes* attributes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System")
		class UHIAbilityData* abilityData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System| Combo System")
		UHIComboManagerComponent* comboSystem;

	UPROPERTY(EditAnywhere, Category = "Ability System| Active Abilities")
		UHIWerewolfAbilitiesDataAsset* comboAbilitiesDataAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System| Gameplay Effects")
		TSubclassOf<class UGameplayEffect> jumpEffect;

	UPROPERTY(Transient)
		UGameplayEffect* jumpEffectRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System| Gameplay Effects")
		TSubclassOf<class UGameplayEffect> climbEffect;

	UPROPERTY(Transient)
		UGameplayEffect* climbEffectRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System| Gameplay Effects")
		TSubclassOf<class UGameplayEffect> jumpExecutionEffect;

	UPROPERTY(Transient)
		UGameplayEffect* jumpExecutionEffectRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System| Gameplay Effects")
		TSubclassOf<class UGameplayEffect> jumpFinisherEffect;

	UPROPERTY(Transient)
		UGameplayEffect* jumpFinisherEffectRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System| Gameplay Effects")
		TSubclassOf<class UGameplayEffect> stopMovingEffect;

	UPROPERTY(Transient)
		UGameplayEffect* stopMovingEffectRef;

	UPROPERTY(Transient)
		UGameplayEffect* RegenerationEffectRef;

	// Distance at which the werewolf will be able to jump to a wall to climb from the floor
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability System| Climbing", meta = (ClampMin = "0.0", ClampMax = "5000.0", UIMin = "0.0", UIMax = "5000.0"))
		float distanceToWallToClimbFromFloor;

	// Distance at which the werewolf will be able to jump to a wall to climb from a building
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability System| Climbing", meta = (ClampMin = "0.0", ClampMax = "5000.0", UIMin = "0.0", UIMax = "5000.0"))
		float distanceToWallToClimbFromBuilding;

	// Speed at which the werewolf will climb
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability System| Climbing", meta = (ClampMin = "0.0", ClampMax = "1000.0", UIMin = "0.0", UIMax = "1000.0"))
		float climbingSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability System| Climbing")
		class AHIWall* targetWall;

	// Distance to the borders of a building at which the werewolf will be able to jump to another building or to execute an enemy from above
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability System| Jump", meta = (ClampMin = "0.0", ClampMax = "1000.0", UIMin = "0.0", UIMax = "1000.0"))
		float distanceToBordersToJump;

	// Distance to the building we want to jump (jump between buildings)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability System| Jump", meta = (ClampMin = "0.0", ClampMax = "10000.0", UIMin = "0.0", UIMax = "10000.0"))
		float distanceToBuildingToJump;

	// Array with the angles (in Z axis with the camera) to the building we want to jump. Check first angle, if not hit, check second, ...
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability System| Jump", meta = (ClampMin = "0.0", ClampMax = "180.0", UIMin = "0.0", UIMax = "180.0"))
		TArray<float> anglesToBuildingToJump;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability System| Finisher", meta = (ClampMin = "0.0", ClampMax = "5000.0", UIMin = "0.0", UIMax = "5000.0"))
		float topExecutionCapsuleRadius;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability System| Finisher", meta = (ClampMin = "0.0", ClampMax = "10000.0", UIMin = "0.0", UIMax = "10000.0"))
		float topExecutionCapsuleHeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability System| Finisher", meta = (ClampMin = "0.0", ClampMax = "10000.0", UIMin = "0.0", UIMax = "10000.0"))
		float sameLevelExecutionDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		AHICameraManager* camManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability System| Finisher")
		class AHIEnemy* enemyToFinisher;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability System| Finisher")
		class AHIEnemy* enemyToFinisherSameLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability System| Finisher")
		class AHIEnemy* enemyToCombatFinisher;

#pragma endregion

#pragma region COMBO_ABILITIES_ATRIBUTES

	UPROPERTY(Transient)
		TArray<UHIComboAbility*> lightAttackComboAbility;
	FEnqueueComboAbilityEvent lightAttackAbilityEvent;

	UPROPERTY(Transient)
		TArray<UHIComboAbility*> heavyAttackComboAbility;
	FEnqueueComboAbilityEvent heavyAttackAbilityEvent;

	UPROPERTY(Transient)
		TArray<UHIComboAbility*> dashComboAbility;
	FEnqueueComboAbilityEvent dashAbilityEvent;

	UPROPERTY(Transient)
		TArray<UHIComboAbility*> howlComboAbility;
	FEnqueueComboAbilityEvent howlAbilityEvent;

#pragma endregion

	UPROPERTY(BlueprintReadOnly, Category = "User Interface")
		UHIVincentHUD* widgetref;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")
		TSubclassOf<UHIVincentHUD> WidgetClass;

	UPROPERTY(EditAnywhere, Category = "User Interface")
		bool debugBarsVisible;

	UPROPERTY(EditAnywhere, Category = "User Interface| Button")
		TSubclassOf<AHIButtonHUD> buttonBP;

	UPROPERTY(Transient)
		class AHIButtonHUD* buttonHUD;

	//Direction input 
	UPROPERTY(BlueprintReadOnly)
		FVector forwardVectorInput;

	UPROPERTY(BlueprintReadOnly)
		FVector sideVectorInput;

	UPROPERTY(BlueprintReadOnly)
		FVector resultVectorInput;

	AHIEnemy* enemygrabbed;

protected:
#pragma region DELEGATES
	FDelegateHandle healthChangedDelegateHandle;
	FDelegateHandle maxHealthChangedDelegateHandle;
	FDelegateHandle rageChangedDelegateHandle;
	FDelegateHandle howlChangedDelegateHandle;
	FDelegateHandle speedChangedDelegateHandle;
#pragma endregion

private:
#pragma region TICK_VARIABLES
	FHitResult outHit;
	FVector startRay;
	FVector endRay;
	FVector forwardVector;
	FCollisionQueryParams collisionParams;
	bool isRayHit;
	bool isClimbing;
	bool isDoingFinisher;

	float healingTick;
	float startHealingHP;
	float timerEQS;
	float elapsedtimerEQS;
	int currentRageLevel = 0;
#pragma  endregion

	float detectionExecutionThreshold;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void HIUpdateEQSQueryPosition(float DeltaTime);
	UFUNCTION(BlueprintCallable)
		void HIApplyRegeneration(float DeltaTime);

	UFUNCTION()
		void ThrowEnemy(AHIEnemy* _enemy);

	UFUNCTION()
		bool HIThrowEnemyGrabbed();

#pragma region GETTERS
	UFUNCTION()
		UCineCameraComponent* HIGetCamera() { return cineCamera; }

	UFUNCTION()
		const UHIWerewolfAttributes* HIGetAttributes() { return attributes; }

	UFUNCTION(BlueprintCallable)
		const float HIGetMaxRage();

	UFUNCTION(BlueprintCallable)
		bool GetIsClimbing() const;

	UFUNCTION(BlueprintCallable)
		void SetIsClimbing(bool _isClimbing);

	UFUNCTION(BlueprintCallable)
		void SetIsDoingFinisher(bool _isDoingFinisher);

	UFUNCTION(BlueprintCallable)
		const float HIGetRage() const;
#pragma endregion

#pragma region ACTIVATE_ABILITIES
	UFUNCTION()
		void HIActivateDash();

	UFUNCTION()
		void HIActivateLightAttack();

	UFUNCTION()
		void HIActivateHeavyAttack();

	UFUNCTION()
		void HIActivateJump();

	UFUNCTION()
		void ActivateClimb();

	UFUNCTION()
		void HIActivateHowl();

	UFUNCTION()
		void HIActivateFinisher();

	UFUNCTION()
		void HIActivateDelegates();

	UFUNCTION(BlueprintImplementableEvent)
		void HINoRageActivated();

	UFUNCTION(BlueprintImplementableEvent)
		void HIRage1Activated();

	UFUNCTION(BlueprintImplementableEvent)
		void HIRage2Activated();

	UFUNCTION(BlueprintImplementableEvent)
		void HIRage3Activated();
#pragma endregion

protected:
#pragma region DELEGATES_FUNCTIONS

	virtual void HIHealthChanged(const FOnAttributeChangeData& Data);
	virtual void HIMaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void HIRageChanged(const FOnAttributeChangeData& Data);
	virtual void HIHowlChanged(const FOnAttributeChangeData& Data);
	virtual void HIspeedChanged(const FOnAttributeChangeData& Data);

#pragma endregion

private:
	void HIInitializeAbilities();

	UFUNCTION()
		void OnHitBegin(AActor* _selfActor, AActor* _otherActor, FVector _normalImpulse, const FHitResult& _hit);

	UFUNCTION()
		/// <summary>
		/// Method that contains all the logic needed to throw the enemy grabbed by the enemy
		/// </summary>
		/// <param name="_enemy"> enemy grabbed to launch </param>
		/// <returns> true if enemy was launched. False if not </returns>
		bool DetachEnemy(AHIEnemy* _enemy);

	bool HIIsOnEdge();

	void SetUpComboAbility(TArray<UHIComboAbility*>& comboAbility, FEnqueueComboAbilityEvent& abilityEvent, FComboAbilityConfiguration& abilityConfiguration);

	bool TopExecution();

	bool JumpToClimb();

	bool JumpBetweenBuildings();

	bool SameLevelExecution();

	bool CombatFinisher();

	void SetInitialValues();

	void SetGameplayEffectsReferences();

	void HIHealingRegeneration(float DeltaTime);





	/// <summary>
	///		Function to check the rays to allow the jump between buildings
	/// </summary>
	/// <param name="anchorageHit_">
	///		The ray hit to the anchorage (to calculate the jumpTargetPosition)
	/// </param>
	/// <returns>
	///		true if we can jump to the building
	///		false if we can't jump to the building
	/// </returns>
	bool HICheckRaysToJumpBetweenBuildings(FHitResult& anchorageHit_);
};
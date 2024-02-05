// @AUTHOR: Carlos

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "HIWeaponConditionStruct.h"
#include "HIEnemyAccessory.generated.h"

UCLASS()
class HOWLOFIRON_API AHIEnemyAccessory : public AActor
{
	GENERATED_BODY()

public:
	AHIEnemyAccessory();

public:
	/// <summary>
	/// Accessory ID
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 accessoryID;

	/// <summary>
	/// Name of the accessory (row name of the datatable)
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FName accessoryName;

	/// <summary>
	/// Mesh of the accessory
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* accessoryMesh;

	/// <summary>
	/// Socket where the accessory is attached
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FName accessorySocketName;

	/// <summary>
	/// Indicates if the accessory is a weapon
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool isWeapon;

	/// <summary>
	/// Indicates if the accessory is active (the mesh is visible)
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool isActive;

	/// <summary>
	/// ShootSocket neccessary to the shoot ability
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (EditCondition = "isWeapon", EditConditionHides))
		FName shootSocketName;

	/// <summary>
	/// Tag that activates the shoot ability of the weapon
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (EditCondition = "isWeapon", EditConditionHides))
		FGameplayTag shootAbilityTriggerTag;

	/// <summary>
	/// Tag of the shoot ability of the weapon
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (EditCondition = "isWeapon", EditConditionHides))
		FGameplayTag shootAbilityTag;

	/// <summary>
	/// Shoot ability of the weapon
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (EditCondition = "isWeapon", EditConditionHides))
		TSubclassOf<class UGameplayAbility> shootAbility;

	/// <summary>
	/// Weapon condition to change to it in the BHV Tree (NONE by default)
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (EditCondition = "isWeapon", EditConditionHides))
		FHIWeaponConditionStruct weaponCondition;
	
	/// <summary>
	/// Properties of the attack (e.g. attack delay, attack duration, ...)
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UDataTable* attackProperties;

	/// <summary>
	/// Droppable when enemy dies
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool droppable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float dropAngle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float dropImpulse;

public:
	UFUNCTION()
		void HIAttachAccessoryToSocket(USkeletalMeshComponent* _skeletalMeshToAttach);

	UFUNCTION()
		void HIDetach();

	/// <summary>
	/// Activate or deactivate the accessory (makes visible or hide the accessory mesh)
	/// </summary>
	UFUNCTION()
		void HISetActive(bool _active);

	/// <summary>
	/// Set collision preset to the accessory mesh
	/// </summary>
	UFUNCTION()
		void HISetCollisionPreset(FName _collisionPresetName);

protected:
	virtual void BeginPlay() override;
};

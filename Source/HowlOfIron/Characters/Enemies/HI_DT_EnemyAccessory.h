// @AUTHOR: Carlos

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "HIWeaponConditionStruct.h"
#include "HI_DT_EnemyAccessory.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct HOWLOFIRON_API FHI_DT_EnemyAccessory : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:
    FHI_DT_EnemyAccessory();
    ~FHI_DT_EnemyAccessory() {};

    /// <summary>
    /// Accessory ID
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 accessoryID;

    /// <summary>
    /// Mesh of the accessory
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TAssetPtr<UStaticMesh> accessoryMesh;

    /// <summary>
    /// Socket where the accessory is attached
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FName accessorySocketName;

    /// <summary>
    /// Collision preset of the accessory
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FName collisionPresetName = FName(TEXT("EnemyProp"));

    /// <summary>
    /// Indicates if the accessory is a weapon
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool isWeapon;

    /// <summary>
    /// Socket where the accessory is attached
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "isWeapon", EditConditionHides))
        FName shootSocketName;

    // @TODO: Check to remove this and let only shootAbility
    /// <summary>
    /// Tag that activates the shoot ability of the weapon
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "isWeapon", EditConditionHides))
        FGameplayTag shootAbilityTriggerTag;

    // @TODO: Check to remove this and let only shootAbility
    /// <summary>
    /// Tag of the shoot ability of the weapon
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "isWeapon", EditConditionHides))
        FGameplayTag shootAbilityTag;

    /// <summary>
    /// Shoot ability of the weapon
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "isWeapon", EditConditionHides))
        TSubclassOf<class UGameplayAbility> shootAbility;

    /// <summary>
    /// Properties of the attack (e.g. attack delay, attack duration, ...)
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "isWeapon", EditConditionHides, DisplayName = "Attack Properties"))
        UDataTable* attackProperties;

    /// <summary>
    /// Indicates if the accessory it's droppable when enemy dies
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool droppable = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "droppable", EditConditionHides, ClampMin = "-180.0", ClampMax = "180.0", UIMin = "-180.0", UIMax = "180.0"))
        float dropAngle = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "droppable", EditConditionHides, ClampMin = "0.0", UIMin = "0.0"))
        float dropImpulse = 0.f;
};
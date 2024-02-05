//Created by Marcos

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include <Abilities/GameplayAbility.h>
#include <Engine/DataAsset.h>
#include "HIComboManagerComponent.h"
#include "HIWerewolfAbilitiesData.generated.h"


USTRUCT(BlueprintType)
struct FComboAbilityConfiguration
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Gameplay Abilities"))
		TArray<TSubclassOf<class UGameplayAbility>> gameplayAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Attach Mode"))
		TEnumAsByte<ComboAbilityAttachMode> attachMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Ability Weight"))
		int abilityWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Ability Priority"))
		int abilityPriority;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Activation Delay"))
		float abilityActivationDelay;

};

UCLASS(BlueprintType)
class HOWLOFIRON_API UHIWerewolfAbilitiesDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo Configuration", meta = (DisplayName = "Max Combo Weight"))
		int maxComboWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo Configuration", meta = (DisplayName = "Coldown beetwen combos"))
		float resetColdown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightAttack", meta = (DisplayName = "AbilityConfiguration"))
		FComboAbilityConfiguration lightAttackConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeavyAttack", meta = (DisplayName = "AbilityConfiguration"))
		FComboAbilityConfiguration heavyAttackConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash", meta = (DisplayName = "AbilityConfiguration"))
		FComboAbilityConfiguration dashConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Howl", meta = (DisplayName = "AbilityConfiguration"))
		FComboAbilityConfiguration howlConfiguration;
	
};

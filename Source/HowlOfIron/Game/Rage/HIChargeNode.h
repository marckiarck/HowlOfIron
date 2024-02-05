//Created by Marcos

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <GameplayEffect.h>
#include <GameplayTagContainer.h>
#include "HIChargeNode.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHIChargeNode : public UObject
{
	GENERATED_BODY()

public:
	UHIChargeNode();

private:
	int chargeNodeFillValue;
	int safeWeight;
	int safeWeightCapacity;
	bool effectsAplied;

	UPROPERTY()
		UHIChargeNode* nextChargeNode;

	UPROPERTY()
		UHIChargeNode* previousChargeNode;

	UPROPERTY()
		TArray<TSubclassOf<UGameplayEffect>> gameplayEffectsToBeApplied;

	UPROPERTY()
		FGameplayTag removeEffectsTag;

	UPROPERTY()
		UAbilitySystemComponent* abilitySytem;

public:
	void HIInitializeChargeNode(int assigendChargeNodeFillValue, int assigendSafeWeightCapacity, UHIChargeNode* assignedPreviousChargeNode, TArray<TSubclassOf<UGameplayEffect>>& assignedEffectsApplied, FGameplayTag assignedTag);
	int HIAddChargeSafeWeight(unsigned int weightAdded);
	int HIRemoveChargeSafeWeight(unsigned int weightRemoved);
	void HIResetSafeWeight();

	UHIChargeNode* HIChargeNextNode();
	UHIChargeNode* HIChargePreviousNode();

	const int HIGetChargeNodeFillValue() const;
	UHIChargeNode* const HIGetNextChargeNode() const;
	UHIChargeNode* const HIGetPreviousChargeNode() const;
	void HISetAbilitySystem(UAbilitySystemComponent* newAbilitySytem);

private:
	void HIApplyEffects();
	void HIRemoveEffects();
};

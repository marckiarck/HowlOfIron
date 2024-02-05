//Created by Marcos

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HIChargeNode.h"
#include "HIChargeHeapDataAsset.h"
#include "HIChargedHeap.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOverloadEventDelegate);

UCLASS(BlueprintType, Blueprintable)
/// <summary>
/// Class that simulates a node heap that acumulates weight. 
/// When the weight is filled it applies gameplay effects and upgrades to the next node. 
/// When the weight reach 0, it removes gameplay effects and downgrade to the previous node
/// </summary>
class HOWLOFIRON_API UHIChargedHeap : public UObject
{
	GENERATED_BODY()

public:
	UHIChargedHeap();
	~UHIChargedHeap();
	
public:
	/// <summary>
	/// Delegate that broadcast when the heap reaches the top
	/// </summary>
	FOverloadEventDelegate OnOverload;

private:
	UPROPERTY()
	UHIChargeNode* currentChargeNode;

	int currentChargeWeight;
	int maxChargedValueWeight;
	bool overloaded;
	float overloadDuration;

	/// <summary>
	/// Timer used to reset charged heap passed overloadDuration seconds
	/// </summary>
	UPROPERTY()
		FTimerHandle OverloadTimerHandle;

	UPROPERTY()
		UAbilitySystemComponent* attachedAbilitySytem;

	/// <summary>
	/// Gameplay effect used to match GAS attribute to the current charge weight value
	/// </summary>
	UPROPERTY()
		TSubclassOf<UGameplayEffect> chargeAttributeeUpdateGameplayEffect;

		UPROPERTY(Transient)
		UGameplayEffect* chargeAttributeeUpdateGameplayEffectRef;

public:
	/// <summary>
	/// Initializes the heap with nodes and chargeAttributeeUpdateGameplayEffect
	/// </summary>
	/// <param name="chargeHeapDataAsset"> DataAsset with the information used to initialize the heap </param>
	void HIInitialize(UHIChargeHeapDataAsset* chargeHeapDataAsset);

	/// <summary>
	/// Attaches an ability system to the heap. Gameplay effects will be applied to the attached ability system.
	/// </summary>
	/// <param name="abilitySystem"> attached ability system </param>
	void HIAttachAbilitySystem(UAbilitySystemComponent* abilitySystem);

	/// <summary>
	/// Adds weight to the charged heap and upgrades the heap to the next charge node if available.
	/// </summary>
	/// <param name="weightAdded"> weight added to the charge node </param>
	void HITryUpgradeChargeNode(unsigned int weightAdded);

	/// <summary>
	/// Removes weight to the charged heap and downgrades the heap to the prebious charge node if available.
	/// </summary>
	/// <param name="weightRemoved"> weight removed to the charged heap </param>
	void HITryDowngradeChargeNode(unsigned int weightRemoved);

	/// <summary>
	/// Returns the value of the weight filled in the current node. 
	/// </summary>
	/// <returns> value of the weight filled in the current node. </returns>
	int HIGetCurrentChargedValue();

	/// <summary>
	/// Reset the charge heap to its initial state, removing gameplay effects applied by the heap.
	/// </summary>
	void HIReset();

	/// <summary>
	/// Empties the heap reseting it.
	/// </summary>
	void HIEmpty();

private:
	/// <summary>
	/// Adds weight to the charged heap
	/// </summary>
	/// <param name="weightAdded"> weight added to the heap </param>
	/// <returns> weight left over after fiil the heap with weightAdded </returns>
	int HIAddChargeWeight(unsigned int weightAdded);

	/// <summary>
	/// Removes weight to the charged heap
	/// </summary>
	/// <param name="wightRemoved"> weight added to the heap </param>
	/// <returns> weight left over after reaching 0 weight in the current node </returns>
	int HIRemoveChargeWeight(unsigned int wightRemoved);

	/// <summary>
	/// Method executed when charged heap reaches the top
	/// </summary>
	void HIOverloadChargeHeap();

	/// <summary>
	/// Calculate the max value the heap can reach after overload
	/// </summary>
	/// <param name="chargeHeapDataAsset"> DataAsset required to calculate the max value </param>
	void HICalculateMaxChargedValueWeight(UHIChargeHeapDataAsset* chargeHeapDataAsset);

	/// <summary>
	/// Calculates the weight of the heap taking into account all nodes already filled.
	/// </summary>
	/// <returns> calculated total charge weight </returns>
	float HICalculateTotalChargeWeight();

	/// <summary>
	/// Returns the value of the GAS attribute associated with the heap
	/// </summary>
	/// <returns> value of the GAS attribute associated with the heap  </returns>
	float HIGetChargedAttributeValue();

	/// <summary>
	/// Updates the state of the heap to match with the GAS attribute associated with the heap
	/// </summary>
	void HIUpdatecurrentChargeWeightBasedOnAttributte();

	/// <summary>
	/// Updates the GAS attribute associated with the heap
	/// </summary>
	/// <param name="expectedAttribute"> value that GAS attribute is going to take </param>
	void HIUpdateAttributeBasedOnCurrentChargeWeight(float expectedAttribute);

	/// <summary>
	/// Delegates that updates the the heap when a gameplay effect is applied
	/// </summary>
	/// <param name="attachedAbilitySytem"> ability system attached to the charged heap </param>
	/// <param name="gameplayEffectSpec"> gameplay effect spec of the applied gameplayEffect </param>
	/// <param name="gameplayEffectHandle"> gameplay effect spec of the applied gameplayEffect </param>
	UFUNCTION()
		void HIUpdateChargedHeapOnGameplayEffectAppliedToSelf(UAbilitySystemComponent* affectedAbilitySytem, const FGameplayEffectSpec& gameplayEffectSpec, FActiveGameplayEffectHandle gameplayEffectHandle);
};

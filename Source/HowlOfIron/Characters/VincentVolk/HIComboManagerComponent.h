//Created by Marcos

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <AbilitySystemComponent.h>
#include "Game/ComboSystem/HIComboQueue.h"
#include "Game/ComboSystem/HIComboAbility.h"
#include <Abilities/GameplayAbility.h>
#include <Components/InputComponent.h>
#include "HIComboManagerComponent.generated.h"

/// <macro>
/// Macro that contains the name of the tag that is going to prevent enqueue abilities to the combo system
/// </macro>
#define CANCEL_ENQUEUE_TAG "Werewolf.Ability.Combo.Cancel.Enqueue"

/// <summary>
/// Delegate designed to attach methods to enqueue UHIComboAbilities
/// </summary>
/// <param name=""> Delegate name </param>
/// <param name=""> Type of the first param of the method attached </param>
/// <param name=""> Name of the first param of the method attached </param>
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnqueueComboAbilityEvent, TArray<UHIComboAbility*>, comboAbilityLaunched);

/// <summary>
/// Enumeration that represents if to enqueue an ability the queue is going to be reseted or not.
/// </summary>
UENUM()
enum ComboAbilityAttachMode {
	ENQUEUE,
	RESET_ENQUEUE,
	RESET_LAUNCH
};

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HOWLOFIRON_API UHIComboManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHIComboManagerComponent();

private:

	/// <summary>
	/// Pointer to the UAbilitySystemComponent that is going to execute abilities when they are dequeued.
	/// </summary>
	UPROPERTY(VisibleAnywhere)
	UAbilitySystemComponent* abilitySystem;

	/// <summary>
	/// Queue where are going to be enquequed and dequeued abilities that UHIComboMangerCompoennt is going to manage 
	/// </summary>
	UPROPERTY(VisibleAnywhere)
	UHIComboQueue* comboQueue;

	/// <summary>
	/// Default max weight of the UHIComboQueue
	/// </summary>
	const int MAX_WEIGHT = 3;

	/// <summary>
	/// Default queue reset cooldown time of the UHIComboQueue
	/// </summary>
	const float QUEUE_RESET_COOLDOWN = 2.f;

	/// <summary>
	/// boolean that check if abilitySystem is throwing an ability or not.
	/// </summary>
	bool launchingAbility;

	/// <summary>
	/// Pointer to the combo ability that is being launched. When there is no ability being launched is nullptr
	/// </summary>
	UPROPERTY(Transient)
	UHIComboAbility* launchedComboAbility;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// <summary>
	/// Assign a UAbilitySystemComponent to abilitySystem pointer,
	/// </summary>
	/// <param name="attachedAbilitySystem"> ability system that is going to be assigned </param>
	void HIAttachAbilitySystem(UAbilitySystemComponent* attachedAbilitySystem);

	/// <summary>
	/// Attach a combo ability delegate to the 
	/// </summary>
	/// <param name="attachEvent"> Delegate that is going to be attached to a method </param>
	/// <param name="attachMode"> attach mode that is going to decide with method will be attached </param>
	void HIAttachComboEvent(FEnqueueComboAbilityEvent& attachEvent, ComboAbilityAttachMode attachMode);

	/// <summary>
	/// Method that will be launched when the ability system will throw an ability
	/// </summary>
	/// <param name="launchedAbility"> Gameplay ability launched </param>
	UFUNCTION()
		void HIOnComboAbilityActivated(UGameplayAbility* launchedAbility);

	/// <summary>
	/// Method that will be launched when a ability launched by the ability system will end 
	/// </summary>
	/// <param name="launchedAbility"></param>
	UFUNCTION()
		void HIOnComboAbilityEnded(UGameplayAbility* launchedAbility);

	/// <summary>
	/// Sets the maximum combo queue weight
	/// </summary>
	/// <param name="comboQueueWeight"> New combo queue max weight </param>
	void HISetComboQueueWeight(int& comboQueueWeight);

	/// <summary>
	/// Sets the reset queue cooldown
	/// </summary>
	/// <param name="resetQueueColdown"> New reset queue cooldown value </param>
	void HISetResetQueueCooldown(float& resetQueueCooldown);

	/// <summary>
	/// Checks if the combo manager can enqueue abilities
	/// </summary>
	/// <returns> true if can enqueue abilities, false if not </returns>
	UFUNCTION()
		const bool CanEnqueueAbility() const;

private:

	/// <summary>
	/// Enqueues a combo ability.
	/// </summary>
	/// <param name="comboAbility"> Combo ability that is going to be enqueued </param>
	UFUNCTION()
		void HIEnqueueAbility(TArray<UHIComboAbility*> comboAbility);

	/// <summary>
	/// Enqueues an ability reseting the queue before
	/// </summary>
	/// <param name="comboAbility"> Combo ability that is going to be enqueued </param>
	UFUNCTION()
		void HIResetComboAndEnqueueAbility(TArray<UHIComboAbility*> comboAbility);

	/// <summary>
	/// Launches an ability reseting the queue before. Ability will not be added to the combo queue
	/// </summary>
	/// <param name="comboAbility"> Combo ability that is going to be launched </param>
	UFUNCTION()
		void HIResetComboAndLaunchAbility(TArray<UHIComboAbility*> comboAbility);

	UFUNCTION()
	/// <summary>
	/// Adds a tag to the abilitySystem which indicates that combo started
	/// </summary>
	/// <exception>
	/// Combo is considered as started when there are at least two abilities enquequed, so if there is 
	/// just one ability enqueue tag will not be added
	/// </exception>
	void HIAddComboTag();

};

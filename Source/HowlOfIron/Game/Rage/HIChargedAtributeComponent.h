//Created by Marcos

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HIChargeHeapDataAsset.h"
#include "HIChargedHeap.h"
#include <GameplayEffect.h>
#include "HIChargedAtributeComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), BlueprintType, Blueprintable)
class HOWLOFIRON_API UHIChargedAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHIChargedAttributeComponent();

private:
	UPROPERTY(EditAnywhere, Category = "AtributeCharges")
		UHIChargeHeapDataAsset* chargeHeapdDataAsset;

	UPROPERTY()
		UHIChargedHeap* attributeChargedHeap;

	/*UPROPERTY()
		UAbilitySystemComponent* attachedAbilitySystem;*/

	UPROPERTY(VisibleAnywhere, Category = "AtributeCharges")
		float chargeLosTicktDelay;

	UPROPERTY()
		float maxChargedValueWeight;

	UPROPERTY()
		float elapsedDeltaTime;  


	UPROPERTY()
	FTimerHandle UpdateChargedHeaptTimerHandle;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void HIAttachAbilitySystem(UAbilitySystemComponent* abilitySystem);

	int HIGetCurrentChargedValue();

	int HIGetMaxChargedValue();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


    void Activate(bool bReset = false) override;


    void Deactivate() override;


private:

	void HICalculateMaxChargedValueWeight();

	void HIInitializeChargeHeap();

	UFUNCTION()
	void HIUpdateChargedHeap();

	UFUNCTION()
	void OverloadFunction();




};

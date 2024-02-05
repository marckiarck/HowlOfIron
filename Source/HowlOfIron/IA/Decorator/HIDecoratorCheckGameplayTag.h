// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <AbilitySystemComponent.h>
#include <BehaviorTree/BTDecorator.h>
#include "HIDecoratorCheckGameplayTag.generated.h"

UCLASS()
class HOWLOFIRON_API UHIDecoratorCheckGameplayTag : public UBTDecorator
{
	GENERATED_BODY()

public:
	UHIDecoratorCheckGameplayTag();
	~UHIDecoratorCheckGameplayTag() {};

private:
	UPROPERTY(EditAnywhere, Category = GameplayTagCheck)
		EGameplayContainerMatchType matchType;

	UPROPERTY(EditAnywhere, Category = GameplayTagCheck)
		FGameplayTagContainer gameplayTags;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData) override;
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

private:
	bool CheckHasAllGameplayTags(UAbilitySystemComponent* ownerAbilitySystem) const;
	bool CheckHasAnyGameplayTags(UAbilitySystemComponent* ownerAbilitySystem) const;
};

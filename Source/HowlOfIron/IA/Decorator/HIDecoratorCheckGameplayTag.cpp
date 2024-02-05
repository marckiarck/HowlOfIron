// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Decorator/HIDecoratorCheckGameplayTag.h"
#include <GameplayTagAssetInterface.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Object.h>

UHIDecoratorCheckGameplayTag::UHIDecoratorCheckGameplayTag()
{
	bNotifyActivation = true;
	bNotifyBecomeRelevant = true;
	bNotifyTick = true;
}

bool UHIDecoratorCheckGameplayTag::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp == NULL)
	{
		return false;
	}

	AAIController* ownerController = Cast<AAIController>(OwnerComp.GetOwner());
	IAbilitySystemInterface* ownerAbilitySystemInterface = Cast<IAbilitySystemInterface>(ownerController->GetPawn());
	if (ownerAbilitySystemInterface == NULL)
	{
		return false;
	}

	UAbilitySystemComponent* abilitySystem = ownerAbilitySystemInterface->GetAbilitySystemComponent();
	switch (matchType)
	{
	case EGameplayContainerMatchType::All:
		return this->CheckHasAllGameplayTags(abilitySystem);
		break;

	case EGameplayContainerMatchType::Any:

		return CheckHasAnyGameplayTags(abilitySystem);
		break;

	default:
	{
		UE_LOG(LogBehaviorTree, Warning, TEXT("Invalid value for TagsToMatch (EGameplayContainerMatchType) %d.  Should only be Any or All."), static_cast<int32>(matchType));
		return false;
	}
	}
}

void UHIDecoratorCheckGameplayTag::OnNodeActivation(FBehaviorTreeSearchData& SearchData)
{
	Super::OnNodeActivation(SearchData);
}

void UHIDecoratorCheckGameplayTag::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	OwnerComp.RequestExecution(this);
}

void UHIDecoratorCheckGameplayTag::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	OwnerComp.RequestExecution(this);
}

bool UHIDecoratorCheckGameplayTag::CheckHasAllGameplayTags(UAbilitySystemComponent* ownerAbilitySystem) const
{
	FGameplayTagContainer OwnedTags;
	ownerAbilitySystem->GetOwnedGameplayTags(OwnedTags);

	return OwnedTags.HasAll(gameplayTags);
}

bool UHIDecoratorCheckGameplayTag::CheckHasAnyGameplayTags(UAbilitySystemComponent* ownerAbilitySystem) const
{
	FGameplayTagContainer OwnedTags;
	ownerAbilitySystem->GetOwnedGameplayTags(OwnedTags);

	return OwnedTags.HasAny(gameplayTags);
}


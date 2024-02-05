// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AnimNotifies/HICancelComboAnimNotifyState.h"
#include <AbilitySystemInterface.h>
#include <AbilitySystemComponent.h>
#include <HIMacros.h>

void UHICancelComboAnimNotifyState::HICancelCombo(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (abilitySystem && abilitySystem->IsValidLowLevel())
	{
		FGameplayTagContainer abilitySystemTags;
		abilitySystem->GetOwnedGameplayTags(abilitySystemTags);
		if (abilitySystemTags.HasTag(GET_GAMEPLAY_TAG(COMBO_TAG)))
		{
			abilitySystem->AddLooseGameplayTag(GET_GAMEPLAY_TAG(END_COMBO_TAG));
		}
	}
	
}

void UHICancelComboAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	IAbilitySystemInterface* abilityCharacter = Cast<IAbilitySystemInterface>(MeshComp->GetOwner());
	if (abilityCharacter)
	{
		abilitySystem = abilityCharacter->GetAbilitySystemComponent();
	}
}

void UHICancelComboAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	HICancelCombo(MeshComp, Animation);
}

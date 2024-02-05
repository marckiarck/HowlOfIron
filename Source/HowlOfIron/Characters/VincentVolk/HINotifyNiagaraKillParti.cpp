// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/VincentVolk/HINotifyNiagaraKillParti.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Particles/ParticleSystemComponent.h"

void UHINotifyNiagaraKillParti::NotifyEnd(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{
	if (UFXSystemComponent* FXComponent = GetSpawnedEffect(MeshComp))
	{
		// untag the component
		FXComponent->ComponentTags.Remove(GetSpawnedComponentTag());

		UAbilitySystemComponent* pAbilityComp =	UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MeshComp->GetOwner());


		if (pAbilityComp && pAbilityComp->HasMatchingGameplayTag(tagToDestroyNotify))
		{
			FXComponent->DestroyComponent();
		}
		else
		{
			FXComponent->Deactivate();
		}
	}

	Super::NotifyEnd(MeshComp, Animation);
}

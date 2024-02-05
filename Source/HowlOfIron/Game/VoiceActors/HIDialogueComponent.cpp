// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/VoiceActors/HIDialogueComponent.h"
#include <Game/Conditions/HIDelegateCondition.h>
#include <Game/Audio/HIAudioStruct.h>

AHIDialogueComponent::AHIDialogueComponent()
{
	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Dialogue Component"));
	HIInitilize();
}

void AHIDialogueComponent::HIInitilize()
{
	audioComponent->bAutoActivate = false;
	audioComponent->bAutoDestroy = false;
}

void AHIDialogueComponent::HIAttachStopCondition(class UHIDelegateCondition* stopCondition)
{

	AHIConditionRegister::HIGetConditionRegister()->HIRegisterCondition(stopCondition, true, true);
	stopCondition->onConditionTriggered.AddDynamic(this, &AHIDialogueComponent::HIStopDialogue);
}

void AHIDialogueComponent::HISetUpConfiguration(FHIAudioStruct configurationRow)
{
	audioComponent->SetSound(configurationRow.sound);
	audioComponent->SetVolumeMultiplier(configurationRow.volume);
	audioComponent->SetPitchMultiplier(configurationRow.pitch);
	audioComponent->AttenuationSettings = configurationRow.attenuation;
}

void AHIDialogueComponent::HIPlayDialogue()
{
	audioComponent->Play();
}

void AHIDialogueComponent::HIStopDialogue(bool conditionMet)
{
	if (conditionMet)
	{
		audioComponent->Stop();
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		AHIObjectPooler_Actors::HIGetObjectPooler()->DespawnItem(this);
	}
}

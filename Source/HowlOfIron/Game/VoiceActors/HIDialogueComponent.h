// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "HIDialogueComponent.generated.h"


UCLASS()
class HOWLOFIRON_API AHIDialogueComponent : public AActor
{
	GENERATED_BODY()

public:
	AHIDialogueComponent();


private:
	UPROPERTY(Transient)
	UAudioComponent* audioComponent;

public:
	void HIInitilize();
	void HIAttachStopCondition(class UHIDelegateCondition* stopCondition);
	void HISetUpConfiguration(struct FHIAudioStruct configurationRow);
	void HIPlayDialogue();

private:
	UFUNCTION()
	void HIStopDialogue(bool conditionMet);

};

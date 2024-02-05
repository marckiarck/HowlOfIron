// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include <GameplayTagContainer.h>
#include "HIAddGameplayTagAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class HOWLOFIRON_API UHIAddGameplayTagAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, meta = (DisplayName = "GameplayTag"))
	FGameplayTag notifiedTag;

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "HIHitAnimAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class HOWLOFIRON_API UHIHitAnimAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, meta = (DisplayName = "ShapePosition"))
	FVector positionOffset;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "SphereRadious"))
	float sphereRadious;
	
public:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "HISetScalarMaterialValue.generated.h"

/**
 * 
 */
UCLASS()
class HOWLOFIRON_API UHISetScalarMaterialValue : public UAnimNotify
{
	GENERATED_BODY()

	public: 
	UPROPERTY(EditAnywhere)
	FName Parameter;

	UPROPERTY(EditAnywhere)
	float Value;

protected:

private:

public:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);

protected:

private:

	
};

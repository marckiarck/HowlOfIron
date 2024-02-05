// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include <GameplayEffect.h>
#include "HISocketSphereCastAnimNotifyState.generated.h"

/**
 * 
 */

UENUM()
enum typeShapeCast {
	CAPSULE,
	BOX,
	SPHERE
};

UCLASS()
class HOWLOFIRON_API UHISocketSphereCastAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
private:


	UPROPERTY(EditAnywhere, meta = (DisplayName = "Use socket"))
		bool  usingSocket;
	
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Shape Distance"))
		float  shapeDistance;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "SocketName", EditCondition = "usingSocket", EditConditionHides))
	FName socketName;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "ShapePosition", EditCondition = "usingSocket", EditConditionHides))
	FVector positionOffset;


	UPROPERTY(EditAnywhere)
	TEnumAsByte<typeShapeCast> shape;


	UPROPERTY(EditAnywhere, meta = ( EditCondition = "shape==typeShapeCast::SPHERE", EditConditionHides))
	float sphereRadious;

	UPROPERTY(EditAnywhere, meta = ( EditCondition = "shape==typeShapeCast::CAPSULE", EditConditionHides))
	float capsuleRadious;

	UPROPERTY(EditAnywhere, meta = ( EditCondition = "shape==typeShapeCast::CAPSULE", EditConditionHides))
	float capsuleHeight;

	UPROPERTY(EditAnywhere, meta = ( EditCondition = "shape==typeShapeCast::BOX", EditConditionHides))
	FVector boxhalfExtended;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "GampelayEffect"))
	TSubclassOf<UGameplayEffect> appliedGameplayEffect;

	class AHIEnemy* targetEnemy;

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AnimNotifies/HISetScalarMaterialValue.h"

void UHISetScalarMaterialValue::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

    MeshComp->SetScalarParameterValueOnMaterials(Parameter,Value);

}

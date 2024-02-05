// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/HIChangeMaterialParameter.h"
#include <Components/SkeletalMeshComponent.h>

UHIChangeMaterialParameter* UHIChangeMaterialParameter::HIChangeMaterialParameter(UGameplayAbility* OwningAbility, USkeletalMeshComponent* _mesh, FName _variableName, float _parameterValue)
{
	UHIChangeMaterialParameter* returnedTask = NewAbilityTask<UHIChangeMaterialParameter>(OwningAbility);
	returnedTask->mesh = _mesh;
	returnedTask->variableName = _variableName;
	returnedTask->parameterValue = _parameterValue;

	return returnedTask;
}

void UHIChangeMaterialParameter::Activate()
{
	Super::Activate();

	FHashedMaterialParameterInfo materialInfo;
	mesh->GetMaterial(0)->GetScalarParameterValue(materialInfo, previousValue);

	mesh->SetScalarParameterValueOnMaterials(variableName, parameterValue);

}

void UHIChangeMaterialParameter::OnDestroy(bool bInOwnerFinished)
{
	mesh->SetScalarParameterValueOnMaterials(variableName, previousValue);

	Super::OnDestroy(bInOwnerFinished);
}

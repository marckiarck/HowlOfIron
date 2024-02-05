// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/HICharacterAttributes.h"
#include "HIEnemiesAttributes.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHIEnemiesAttributes : public UHICharacterAttributes
{
    GENERATED_BODY()

public:

    UHIEnemiesAttributes();

public:


    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData frequencyShoot;

//@Todo Quitar atributos
	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
		FGameplayAttributeData detectionDistance;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
		FGameplayAttributeData maxDetectionMeter;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
		FGameplayAttributeData accuracyMultiplier;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
		FGameplayAttributeData visionCone;



protected:


private:


public:
    
    ATTRIBUTE_ACCESSORS(UHIEnemiesAttributes, frequencyShoot)
    ATTRIBUTE_ACCESSORS(UHIEnemiesAttributes, detectionDistance)
	ATTRIBUTE_ACCESSORS(UHIEnemiesAttributes, maxDetectionMeter)
	ATTRIBUTE_ACCESSORS(UHIEnemiesAttributes, accuracyMultiplier)
	ATTRIBUTE_ACCESSORS(UHIEnemiesAttributes, visionCone)

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	void PostGameplayEffectExecute_SingleAttribute(const struct FGameplayEffectModCallbackData& Data, FName MemberName, FGameplayAttributeData& Attrib, FGameplayAttributeData& MaxAttrib);

protected:


private:


};

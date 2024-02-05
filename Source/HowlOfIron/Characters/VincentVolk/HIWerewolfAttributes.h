// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/HICharacterAttributes.h"
#include "HIWerewolfAttributes.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHIWerewolfAttributes : public UHICharacterAttributes
{
    GENERATED_BODY()

public:
    UHIWerewolfAttributes();


public:
    

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData run; 
    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData howl;
	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
		FGameplayAttributeData lifesteal;
	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
		FGameplayAttributeData armour;
	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
		FGameplayAttributeData stunTime;
	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
		FGameplayAttributeData survivalMargin;

    #pragma region GAME_DESIGNERS_ATTRIBUTES

    #pragma endregion

protected:

private:

public:
    
    ATTRIBUTE_ACCESSORS(UHIWerewolfAttributes, armour)
    ATTRIBUTE_ACCESSORS(UHIWerewolfAttributes, run)
    ATTRIBUTE_ACCESSORS(UHIWerewolfAttributes, howl)
    ATTRIBUTE_ACCESSORS(UHIWerewolfAttributes, lifesteal)
    ATTRIBUTE_ACCESSORS(UHIWerewolfAttributes, stunTime)
    ATTRIBUTE_ACCESSORS(UHIWerewolfAttributes, survivalMargin)
 
    #pragma region GAME_DESIGNERS_ATTRIBUTES_ACCESSORS

    #pragma endregion

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

protected:

private:

};

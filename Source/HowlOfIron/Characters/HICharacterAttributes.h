// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "HICharacterAttributes.generated.h"


// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)




UCLASS()
class HOWLOFIRON_API UHICharacterAttributes : public UAttributeSet
{

    GENERATED_BODY()

public:

    UHICharacterAttributes();


public:
    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData maxHealth;

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData health;

	UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly, meta = (DisplayName = "Rage / fear"))
		FGameplayAttributeData chargedValue;

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData damage1;

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData damage2;    
        
    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData damage3;

    UPROPERTY(Category = "Ability System | Attributes", VisibleAnywhere, BlueprintReadOnly)
        FGameplayAttributeData speed;


    #pragma region GAME_DESIGNERS_ATTRIBUTES

    #pragma endregion

protected:

private:

public:

    ATTRIBUTE_ACCESSORS(UHICharacterAttributes, maxHealth)
    ATTRIBUTE_ACCESSORS(UHICharacterAttributes, health)
    ATTRIBUTE_ACCESSORS(UHICharacterAttributes, damage1)
    ATTRIBUTE_ACCESSORS(UHICharacterAttributes, damage2)
    ATTRIBUTE_ACCESSORS(UHICharacterAttributes, damage3)
    ATTRIBUTE_ACCESSORS(UHICharacterAttributes, speed)
    ATTRIBUTE_ACCESSORS(UHICharacterAttributes, chargedValue)


    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData &Data) override;
     void PostGameplayEffectExecute_SingleAttribute(const struct FGameplayEffectModCallbackData& Data, FName MemberName, FGameplayAttributeData& Attrib, FGameplayAttributeData& MaxAttrib);

protected:

private:


};

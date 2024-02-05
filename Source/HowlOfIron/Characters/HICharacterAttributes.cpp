// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/HICharacterAttributes.h"
#include <GameplayEffectExtension.h>

UHICharacterAttributes::UHICharacterAttributes()
{

}

void UHICharacterAttributes::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    // float coso1 = Attribute.GetNumericValue(this);
    if (Attribute.GetUProperty() == FindFieldChecked<FProperty>(UHICharacterAttributes::StaticClass(), GET_MEMBER_NAME_CHECKED(UHICharacterAttributes, health)))
    {
       // GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("preHealth: %f"), coso1));
         NewValue = FMath::Clamp(NewValue, 0.0f, maxHealth.GetCurrentValue());
    }

}



void UHICharacterAttributes::PostGameplayEffectExecute_SingleAttribute(const struct FGameplayEffectModCallbackData& Data, FName MemberName, FGameplayAttributeData& Attrib, FGameplayAttributeData& MaxAttrib)
{
// Data.EvaluatedData.Attribute.GetUProperty()
    if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UHICharacterAttributes::StaticClass(), MemberName))
    {
        // en verdad el clampeo debería estar en PreAttributeChange
        Attrib.SetCurrentValue(FMath::Clamp(Attrib.GetCurrentValue(), 0.0f, MaxAttrib.GetCurrentValue()));
        Attrib.SetBaseValue(FMath::Clamp(Attrib.GetBaseValue(), 0.0f, MaxAttrib.GetBaseValue()));


    }
}



void UHICharacterAttributes::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{

    Super::PostGameplayEffectExecute(Data);

    PostGameplayEffectExecute_SingleAttribute(Data, GET_MEMBER_NAME_CHECKED(UHICharacterAttributes, health), health, maxHealth);

}
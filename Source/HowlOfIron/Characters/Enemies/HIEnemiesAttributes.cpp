// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/HIEnemiesAttributes.h"
#include <GameplayEffectExtension.h>

UHIEnemiesAttributes::UHIEnemiesAttributes() : Super::UHICharacterAttributes()
{

}


void UHIEnemiesAttributes::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

}



void UHIEnemiesAttributes::PostGameplayEffectExecute_SingleAttribute(const struct FGameplayEffectModCallbackData& Data, FName MemberName, FGameplayAttributeData& Attrib, FGameplayAttributeData& MaxAttrib)
{
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UHIEnemiesAttributes::StaticClass(), MemberName))
	{
		// en verdad el clampeo debería estar en PreAttributeChange
		Attrib.SetCurrentValue(FMath::Clamp(Attrib.GetCurrentValue(), 0.0f, MaxAttrib.GetCurrentValue()));
		Attrib.SetBaseValue(FMath::Clamp(Attrib.GetBaseValue(), 0.0f, MaxAttrib.GetBaseValue()));
	}
}



void UHIEnemiesAttributes::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{

	Super::PostGameplayEffectExecute(Data);

}
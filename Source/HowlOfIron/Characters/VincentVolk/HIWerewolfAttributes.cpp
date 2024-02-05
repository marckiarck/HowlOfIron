// Fill out your copyright notice in the Description page of Project Settings.


#include "HIWerewolfAttributes.h"

UHIWerewolfAttributes::UHIWerewolfAttributes() : Super::UHICharacterAttributes()
{

}

void UHIWerewolfAttributes::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute.GetUProperty() == FindFieldChecked<FProperty>(UHIWerewolfAttributes::StaticClass(), GET_MEMBER_NAME_CHECKED(UHIWerewolfAttributes, armour)))
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, 1.f);
	}

	if (Attribute.GetUProperty() == FindFieldChecked<FProperty>(UHIWerewolfAttributes::StaticClass(), GET_MEMBER_NAME_CHECKED(UHIWerewolfAttributes, howl)))
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, 1.f);
	}

	if (Attribute.GetUProperty() == FindFieldChecked<FProperty>(UHIWerewolfAttributes::StaticClass(), GET_MEMBER_NAME_CHECKED(UHIWerewolfAttributes, survivalMargin)))
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, 1.f);
	}
}

void UHIWerewolfAttributes::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UHIWerewolfAttributes::StaticClass(), GET_MEMBER_NAME_CHECKED(UHIWerewolfAttributes, armour)))
	{
		// en verdad el clampeo debería estar en PreAttributeChange
		armour.SetCurrentValue(FMath::Clamp(armour.GetCurrentValue(), 0.0f, 1.f));
		armour.SetBaseValue(FMath::Clamp(armour.GetBaseValue(), 0.0f, 1.f));
	}

	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UHIWerewolfAttributes::StaticClass(), GET_MEMBER_NAME_CHECKED(UHIWerewolfAttributes, howl)))
	{
		// en verdad el clampeo debería estar en PreAttributeChange
		howl.SetCurrentValue(FMath::Clamp(howl.GetCurrentValue(), 0.0f, 1.f));
		howl.SetBaseValue(FMath::Clamp(howl.GetBaseValue(), 0.0f, 1.f));
	}

	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UHIWerewolfAttributes::StaticClass(), GET_MEMBER_NAME_CHECKED(UHIWerewolfAttributes, survivalMargin)))
	{
		// en verdad el clampeo debería estar en PreAttributeChange
		survivalMargin.SetCurrentValue(FMath::Clamp(survivalMargin.GetCurrentValue(), 0.0f, 1.f));
		survivalMargin.SetBaseValue(FMath::Clamp(survivalMargin.GetBaseValue(), 0.0f, 1.f));
	}
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/HIAbilityCharacter.h"
#include "Characters/VincentVolk/HIWerewolf.h"
#include "Game/HIGameData.h"
#include "HIMacros.h"

AHIAbilityCharacter::AHIAbilityCharacter()
{
    abilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>("AbilityComponent");

    ChargedAttributteComponent = CreateDefaultSubobject<UHIChargedAttributeComponent>("chargedValueAttribute");
}

UAbilitySystemComponent* AHIAbilityCharacter::GetAbilitySystemComponent() const
{
    return abilitySystem;
}

void AHIAbilityCharacter::HISetCharacterType(VoiceDatatableCharType charType)
{
    characterType = charType;
}

const bool AHIAbilityCharacter::HICharacterDead() const
{
    ensureMsgf(this, TEXT("JAJA XD no existo"));
    if (abilitySystem)
    {
        return abilitySystem->HasMatchingGameplayTag(GET_GAMEPLAY_TAG(DEAD_TAG));
    }
    return false;
}

const AHIAbilityCharacter* AHIAbilityCharacter::HIGetWerewolf() const
{
    return UHIGameData::HIGetPlayerWerewolf();
}

FString AHIAbilityCharacter::HIGetVoiceString()
{
	switch (characterType)
	{
	case VoiceDatatableCharType::HUNTER:
	{
		return FString(TEXT("HU"));
	};
	break;
	case  VoiceDatatableCharType::MUTTON:
	{
		return FString(TEXT("MU"));
	};
	break;
	case VoiceDatatableCharType::WEREWOLF:
	{
		return FString(TEXT("WW"));
	};
	break;
	case VoiceDatatableCharType::OWLMAN:
	{
		return FString(TEXT("OW"));
	}
	default:
	{
		return FString(TEXT("MU"));
	};
	break;
	}
}

void AHIAbilityCharacter::BeginPlay()
{
    Super::BeginPlay();

    ChargedAttributteComponent->HIAttachAbilitySystem(abilitySystem);
}

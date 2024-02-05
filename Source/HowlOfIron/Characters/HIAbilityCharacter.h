//Created by Marcos

#pragma once

#include "CoreMinimal.h"
#include "Characters/HICharacter.h"
#include <Game/Rage/HIChargedAtributeComponent.h>
#include "AbilitySystemInterface.h"
#include "HIAbilityCharacter.generated.h"

UENUM()
enum VoiceDatatableCharType {
	WEREWOLF,
	MUTTON,
	HUNTER,
	OWLMAN
};


UCLASS()
class HOWLOFIRON_API AHIAbilityCharacter : public AHICharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AHIAbilityCharacter();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rage", Transient)
		UHIChargedAttributeComponent* ChargedAttributteComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System", meta = (AllowPrivateAccess = "true")) // @TODO: No aparece el inspector
		UAbilitySystemComponent* abilitySystem;

private:
	UPROPERTY(VisibleAnywhere, Category="Voice Acting")
	TEnumAsByte<VoiceDatatableCharType> characterType = MUTTON;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UFUNCTION(BlueprintCallable)
	const AHIAbilityCharacter* HIGetWerewolf() const; 

	UFUNCTION(BlueprintCallable)
	const bool HICharacterDead() const;

	void HISetCharacterType(VoiceDatatableCharType charType);

	UFUNCTION()
		virtual FString HIGetVoiceString();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};

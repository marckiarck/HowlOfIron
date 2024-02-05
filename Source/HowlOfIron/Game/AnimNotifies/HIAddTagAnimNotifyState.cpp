#include "Game/AnimNotifies/HIAddTagAnimNotifyState.h"
#include "Characters/VincentVolk/HIWerewolf.h"

void UHIAddTagAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	UWorld* affectedWorld = MeshComp->GetWorld();
	if (affectedWorld) {
		AHIAbilityCharacter* abilityCharacter = Cast<AHIAbilityCharacter>(MeshComp->GetOwner());

		if (abilityCharacter) {
			abilityCharacter->GetAbilitySystemComponent()->AddLooseGameplayTag(notifiedTag);
		}
	}
}

void UHIAddTagAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UWorld* affectedWorld = MeshComp->GetWorld();
	if (affectedWorld) {
		AHIAbilityCharacter* abilityCharacter = Cast<AHIAbilityCharacter>(MeshComp->GetOwner());

		if (abilityCharacter) {
			abilityCharacter->GetAbilitySystemComponent()->RemoveLooseGameplayTag(notifiedTag);
		}
	}
}

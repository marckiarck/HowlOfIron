#include "Game/AnimNotifies/HIAddGameplayTagAnimNotify.h"
#include "Characters/VincentVolk/HIWerewolf.h"

void UHIAddGameplayTagAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UWorld* affectedWorld = MeshComp->GetWorld();
	if (affectedWorld) 
	{
		AHIAbilityCharacter* abilityCharacter = Cast<AHIAbilityCharacter>(MeshComp->GetOwner());

		if (abilityCharacter) 
		{
			abilityCharacter->GetAbilitySystemComponent()->AddLooseGameplayTag(notifiedTag);
		}
	}

}
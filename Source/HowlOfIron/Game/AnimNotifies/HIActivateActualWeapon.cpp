
#include "Game/AnimNotifies/HIActivateActualWeapon.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Enemies/HIEnemy.h"
#include "Characters/Enemies/HIEnemyAccessory.h"
#include "Characters/Enemies/HIEnemyController.h"
#include "Characters/HIAbilityCharacter.h"

void UHIActivateActualWeapon::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UWorld* affectedWorld = MeshComp->GetWorld();
	if (affectedWorld)
	{
		AHIAbilityCharacter* abilityCharacter = Cast<AHIAbilityCharacter>(MeshComp->GetOwner());
		if (abilityCharacter)
		{
			AHIEnemy* enemy = Cast<AHIEnemy>(abilityCharacter);
			if (enemy)
			{
				enemy->previousWeapon->HISetActive(false);
				enemy->actualWeapon->HISetActive(true);
				UBlackboardComponent* blackboard = enemy->GetController<AHIEnemyController>()->GetBlackboardComponent();
				if (blackboard)
				{
					blackboard->ClearValue("ChangeWeapon");
				}
			}
		}
	}
}

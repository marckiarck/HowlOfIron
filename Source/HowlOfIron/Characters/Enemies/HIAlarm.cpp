
#include "Characters/Enemies/HIAlarm.h"
#include "Game/HIGameData.h"
#include "HIMacros.h"
#include "HI_DT_EnemyAccessory.h"

AHIAlarm::AHIAlarm()
{

}

AHIPatrol* AHIAlarm::HIGetPatrolOwner() const
{
	return patrolOwner;
}

void AHIAlarm::HISetPatrolOwner(AHIPatrol* _patrol)
{
	patrolOwner = _patrol;
}

void AHIAlarm::HIActivate()
{
	AHIEnemy* enemy = Cast<AHIEnemy>(GetAttachParentActor());
	if (!enemy)
	{
		enemy = patrolOwner->HIGetNearestEnemy(GetActorLocation());
	}
	if (enemy)
	{
		enemy->GetAbilitySystemComponent()->AddLooseGameplayTag(GET_GAMEPLAY_TAG(COMBAT_ALARM_TAG));
		enemy->alarmAssigned = this;
	}
}

void AHIAlarm::BeginPlay()
{
	Super::BeginPlay();

	if (accessoriesDataTable)
	{
		FString ContextString = TEXT("Data table context");
		FHI_DT_EnemyAccessory* Row = nullptr;
		TArray<FName> RowNames = accessoriesDataTable->GetRowNames();

		Row = accessoriesDataTable->FindRow<FHI_DT_EnemyAccessory>(alarmRowInDataTable, ContextString, true);
		if (Row)
		{
			accessoryID = Row->accessoryID;
			accessoryName = alarmRowInDataTable;
			accessoryMesh->SetStaticMesh(Row->accessoryMesh.LoadSynchronous());
			accessorySocketName = Row->accessorySocketName;
			HISetCollisionPreset(Row->collisionPresetName);
			isWeapon = Row->isWeapon;
			isActive = true;
			shootSocketName = Row->shootSocketName;
			shootAbilityTriggerTag = Row->shootAbilityTriggerTag;
			shootAbilityTag = Row->shootAbilityTag;
			shootAbility = Row->shootAbility;
			FHIWeaponConditionStruct alarmWeaponCondition;
			weaponCondition = alarmWeaponCondition;
			attackProperties = Row->attackProperties;
			droppable = Row->droppable;
			dropAngle = Row->dropAngle;
			dropImpulse = Row->dropImpulse;
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("AHIAlarm: No Datatable accessories."));
	}
}

TArray<FName> AHIAlarm::HIGetEnemyAccessoriesRowNames()
{
	return UHIGameData::HIGetEnemyAccessoriesRowNames();
}
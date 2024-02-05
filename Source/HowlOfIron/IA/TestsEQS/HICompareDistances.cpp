// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/TestsEQS/HICompareDistances.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h"

UHICompareDistances::UHICompareDistances()
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_VectorBase::StaticClass();
}

void UHICompareDistances::RunTest(FEnvQueryInstance& QueryInstance) const
{

	UObject* QueryOwner = QueryInstance.Owner.Get();
	AHIEnemy* enemy = Cast<AHIEnemy>(QueryOwner);
	AHIEnemyController* enemyController = enemy->GetController<AHIEnemyController>();

	int32 ownerRing = enemyController->GetBlackboardComponent()->GetValueAsInt(FName("CombatRing"));

	if (enemy == nullptr)
	{
		return;
	}

	FVector enemyLocation = enemy->GetActorLocation();
	FVector playerLocation = UHIGameData::HIGetWerewolfLocation();

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		FVector itemLocation = GetItemLocation(QueryInstance, It.GetIndex());

		if (FVector::DistSquared(enemyLocation, itemLocation) < FVector::DistSquared(playerLocation, itemLocation))
		{
			It.ForceItemState(EEnvItemStatus::Passed);
		}
		else 
		{
			It.ForceItemState(EEnvItemStatus::Failed);
		}
		
	}

}
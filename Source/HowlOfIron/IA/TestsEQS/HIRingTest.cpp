// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/TestsEQS/HIRingTest.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Item.h"
#include "Game/HIGameData.h"

UEnvQueryTest_RingTest::UEnvQueryTest_RingTest(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_VectorBase::StaticClass();
}

FText UEnvQueryTest_RingTest::GetDescriptionTitle() const
{

	return FText::FromName(FName(TEXT("Filter enemies by Rings")));
}
FText UEnvQueryTest_RingTest::GetDescriptionDetails() const
{

	return FText::FromName(FName(TEXT("Filter when there are more than x enemies in the Ring")));

}

void UEnvQueryTest_RingTest::RunTest(FEnvQueryInstance& QueryInstance) const
{

	UObject* QueryOwner = QueryInstance.Owner.Get();
	AHIEnemy* enemy = Cast<AHIEnemy>(QueryOwner);
	AHIEnemyController* enemyController = enemy->GetController<AHIEnemyController>();

	int32 ownerRing = enemyController->GetBlackboardComponent()->GetValueAsInt(FName("CombatRing"));

	if (enemy == nullptr)
	{
		return;
	}


	bool checkInRing = false;

	switch (RingToCheck)
	{
		case EEnvTestRing::Ring1:
		{

			if (UHIGameData::HIGetEnemiesFirstRingArray().Find(enemy) != INDEX_NONE)
			{ 
				checkInRing = true;
			}

		}
		break;

		case EEnvTestRing::Ring2:
		{
			if (UHIGameData::HIGetEnemiesSecondRingArray().Find(enemy) != INDEX_NONE)
			{
				checkInRing = true;
			}
		}
		break;

		case EEnvTestRing::Ring3:
		{
			checkInRing = true;
		}
		break;

		default:
		break;
	}


	if (checkInRing)
	{
		for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
		{
			It.ForceItemState(EEnvItemStatus::Passed);
		}

	}
	else
	{
		for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
		{
			It.ForceItemState(EEnvItemStatus::Failed);
		}
	}
	
}

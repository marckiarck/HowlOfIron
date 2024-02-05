// Created by Pablo

#include "HIObjectPooler_Actors.h"
#include "Engine/DataTable.h"
#include "../Characters/Enemies/HIEnemy.h"
#include "Game/HIGameData.h"

AHIObjectPooler_Actors* AHIObjectPooler_Actors::instance = nullptr;

AHIObjectPooler_Actors::AHIObjectPooler_Actors()
{
	PrimaryActorTick.bCanEverTick = true;
}


AHIObjectPooler_Actors* AHIObjectPooler_Actors::HIGetObjectPooler(UWorld* ownerWorld)
{
	
	if (instance == nullptr)
	{
		ensureMsgf(ownerWorld, TEXT("OwnerWorld is nullptr"));
		FActorSpawnParameters paramet;
		AActor* objectPooler = ownerWorld->SpawnActor<AActor>(AHIObjectPooler_Actors::StaticClass(), FVector(0), FRotator(0), paramet);
		instance = Cast<AHIObjectPooler_Actors>(objectPooler);
	}

	return instance;
}

void AHIObjectPooler_Actors::HIResetObjectPooler()
{
	instance = nullptr;
}

//returns an object of the class you indicate. If there is no avaliable, it adds a new one
AActor* AHIObjectPooler_Actors::GetObjectFromPool(UClass* objectClass, AActor* spawnOwner)
{
	CleanPool();

	for (int i = 0; i < pool.Num(); ++i)
	{
		if (pool[i]->GetClass() == objectClass)
		{
			if (pool[i]->IsHidden())
			{
				AActor* returnedActor = pool[i];
				if (returnedActor->GetLevel() == spawnOwner->GetLevel())
				{
					return returnedActor;
				}
			}
		}
	}

	FActorSpawnParameters paramet;
	if (spawnOwner == nullptr)
	{
		paramet.Owner = this;
	}
	else {
		paramet.Owner = spawnOwner;
	}
	AActor* object = GetWorld()->SpawnActor<AActor>(objectClass, FVector(0, 0, 10000), FRotator(0), paramet);

	if (object)
	{
		object->SetActorHiddenInGame(true);
		object->SetActorTickEnabled(false);
		object->SetActorEnableCollision(false);

		AHIEnemy* enem = Cast<AHIEnemy>(object);
		if (enem)
		{
			UHIGameData::HIAddEnemyToArray(enem);
		}

		pool.Add(object);
	}

	return object;
}

void AHIObjectPooler_Actors::AddController(AActor* _enemy)
{
	APawn* pawn = Cast<APawn>(_enemy);

	FActorSpawnParameters paramet;
	paramet.OverrideLevel = this->GetLevel();
	AActor* control = GetWorld()->SpawnActor<AActor>(pawn->AIControllerClass, FVector().ZeroVector, FRotator().ZeroRotator, paramet);

	AHIcontrollers.Add(control);
	AHIcontrPossession.Add(false);
}

void AHIObjectPooler_Actors::CleanPool()
{
	TArray<AActor*> cleanPool;

	for (AActor* iter : pool) 
	{
		if (iter)
		{
			cleanPool.Add(iter);
		}
	}

	pool = cleanPool;
}

//disables an object
void AHIObjectPooler_Actors::DespawnItem(AActor* item)
{
	item->SetActorHiddenInGame(true);
	item->SetActorTickEnabled(false);
	item->SetActorEnableCollision(false);

	TArray<AActor*> attachedActors;
	item->GetAttachedActors(attachedActors);
	for (AActor* attachedActor : attachedActors)
	{
		attachedActor->SetActorHiddenInGame(true);
	}

	if (item->GetClass()->IsChildOf(AHIEnemy::StaticClass()))
	{
		APawn* pawn = Cast<APawn>(item);

		AActor* cont = Cast<AActor>(pawn->GetController());

		int32 AHIcontr = AHIcontrollers.Num();

		for (int i = 0; i < AHIcontr; ++i)
		{
			if (AHIcontrollers[i] == cont)
			{
				AHIEnemyController* acont = Cast<AHIEnemyController>(AHIcontrollers[i]);
				acont->UnPossess();

				AHIcontrPossession[i] = false;
			}
		}
	}
}


//Default spawn, adds a controller if needed
void AHIObjectPooler_Actors::spawnItem(AActor* object, FVector _loc)
{
	object->SetActorLocation(_loc);
	object->SetActorHiddenInGame(false);
	object->SetActorTickEnabled(true);
	object->SetActorEnableCollision(true);

	TArray<AActor*> attachedActors;
	object->GetAttachedActors(attachedActors);
	for (AActor* attachedActor : attachedActors)
	{
		attachedActor->SetActorHiddenInGame(false);
	}

	if (object->GetClass()->IsChildOf(AHIEnemy::StaticClass()))
	{
		int32 AHIcontr = AHIcontrollers.Num();

		for (int i = 0; i < AHIcontr; ++i)
		{
			if (!AHIcontrPossession[i])
			{
				APawn* pawn = Cast<APawn>(object);
				AHIEnemyController* acont = Cast<AHIEnemyController>(AHIcontrollers[i]);
				acont->Possess(pawn);

				AHIcontrPossession[i] = true;
			}
		}
	}
}

//creates all the elements of the pool indicated in the associated DataTable
void AHIObjectPooler_Actors::BeginPlay()
{
	Super::BeginPlay();

	UWorld* const world = GetWorld();

	if (world && dataTable)
	{
		TArray<FName> RowNames = dataTable->GetRowNames();
		int32 nRows = RowNames.Num();

		for (int i = 0; i < nRows; ++i)
		{
			int j = dataTable->FindRow<FHI_PooledObject>(RowNames[i], "")->amount;

			for (int k = 0; k < j; ++k)
			{
				FString ContextString = TEXT("Data table context");
				FHI_PooledObject* Row = dataTable->FindRow<FHI_PooledObject>(RowNames[i], ContextString, true);

				UClass* objectClass = Row->item;
				AActor* object;

				FActorSpawnParameters paramet;
				paramet.OverrideLevel = this->GetLevel();
				object = world->SpawnActor<AActor>(objectClass, FVector().ZeroVector, FRotator().ZeroRotator, paramet);

				object->SetActorHiddenInGame(true);
				object->SetActorTickEnabled(false);
				object->SetActorEnableCollision(false);

				pool.Add(object);
			}
		}
	}
}


void AHIObjectPooler_Actors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


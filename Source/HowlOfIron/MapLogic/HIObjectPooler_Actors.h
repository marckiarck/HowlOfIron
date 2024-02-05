// Created by Pablo

#pragma once

#include "CoreMinimal.h"
#include "HIPooledObject.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "../Characters/Enemies/HIEnemyController.h"
#include "HIObjectPooler_Actors.generated.h"

UCLASS()
class HOWLOFIRON_API AHIObjectPooler_Actors : public AActor
{
	GENERATED_BODY()

public:

	static AHIObjectPooler_Actors* instance;

	UPROPERTY(EditAnywhere, Category = "ObjectPooler")
		UDataTable* dataTable;

	UPROPERTY(VisibleAnywhere, Category = "ObjectPooler")
		TArray<AActor*> pool;

	UPROPERTY(VisibleAnywhere, Category = "ObjectPooler")
		TArray<AActor*> AHIcontrollers;

	UPROPERTY(VisibleAnywhere, Category = "ObjectPooler")
		TArray<bool> AHIcontrPossession;


protected:

	virtual void BeginPlay() override;

public:

	AHIObjectPooler_Actors();

	UFUNCTION(BlueprintPure)
		static AHIObjectPooler_Actors* HIGetObjectPooler(UWorld* ownerWorld = nullptr);

	UFUNCTION()
	static void HIResetObjectPooler();

	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
		void spawnItem(AActor* object, FVector _loc);

	UFUNCTION(BlueprintCallable)
		void DespawnItem(AActor* item);

	UFUNCTION(BlueprintCallable)
		AActor* GetObjectFromPool(UClass* objectClass, AActor* spawnOwner);

	UFUNCTION()
		void AddController(AActor* _enemy);

	UFUNCTION()
		void CleanPool();
};

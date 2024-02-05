// @AUTHOR: Carlos

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HIEnemyAccessory.h"
#include "IA/HIPatrol.h"
#include "HIAlarm.generated.h"

// Alarm of the white mutton
UCLASS()
class HOWLOFIRON_API AHIAlarm : public AHIEnemyAccessory
{
	GENERATED_BODY()
	
public:	
	AHIAlarm();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DataTable)
		UDataTable* accessoriesDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DataTable, meta = (GetOptions = "HIGetEnemyAccessoriesRowNames"))
		FName alarmRowInDataTable = FName(TEXT("Alarm"));

	/// <summary>
	/// Reinforcements that will be called from this alarm
	/// </summary>
	UPROPERTY()
		TArray<FHIReinforcement> alarmReinforcements;

private:
	/// <summary>
	/// Patrol associated to this alarm
	/// </summary>
	UPROPERTY(Transient)
		AHIPatrol* patrolOwner;

public:
	UFUNCTION()
		AHIPatrol* HIGetPatrolOwner() const;

	UFUNCTION()
		void HISetPatrolOwner(AHIPatrol* _patrol);

	/// <summary>
	/// Activate the alarm. Notify the corresponding enemy.
	/// </summary>
	UFUNCTION()
		void HIActivate();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		TArray<FName> HIGetEnemyAccessoriesRowNames();
};

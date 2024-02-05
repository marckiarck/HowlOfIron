// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HI_Requisit.generated.h"

UENUM(BlueprintType)
enum class MissionReq : uint8
{
	DEATH_MUTTON = 0 UMETA(DisplayName = "DEATH_MUTTON"),
	DEATH_WHITE_MUTTON = 1 UMETA(DisplayName = "DEATH_WHITE_MUTTON"),
	DEATH_GREEN_MUTTON = 2 UMETA(DisplayName = "DEATH_GREEN_MUTTON"),
	DEATH_YELLOW_MUTTON = 3 UMETA(DisplayName = "DEATH_YELLOW_MUTTON"),
	DEATH_OWLMAN = 4  UMETA(DisplayName = "DEATH_OWLMAN"),
	DEATH_HUNTER = 5     UMETA(DisplayName = "DEATH_HUNTER"),
	DEATH_BOSS = 6     UMETA(DisplayName = "DEATH_BOSS"),
	DEATH_BOILER = 7     UMETA(DisplayName = "DEATH_BOILER"),
	REACH_POSITION1 = 8     UMETA(DisplayName = "REACH_POSITION1"),
	REACH_POSITION2 = 9     UMETA(DisplayName = "REACH_POSITION2"),
	REACH_POSITION3 = 10     UMETA(DisplayName = "REACH_POSITION3"),
	REACH_POSITION4 = 11     UMETA(DisplayName = "REACH_POSITION4"),
	REACH_POSITION5 = 12    UMETA(DisplayName = "REACH_POSITION5"),
	REACH_POSITION6 = 13     UMETA(DisplayName = "REACH_POSITION6"),
	REACH_POSITION7 = 14    UMETA(DisplayName = "REACH_POSITION7"),
	REACH_POSITION8 = 15     UMETA(DisplayName = "REACH_POSITION8"),
	REACH_POSITION9 = 16     UMETA(DisplayName = "REACH_POSITION9"),
	REACH_INTERACT_OBJECT1 = 17    UMETA(DisplayName = "INTERACT_OBJECT1"),
	REACH_INTERACT_OBJECT2 = 18    UMETA(DisplayName = "INTERACT_OBJECT2"),
	REACH_INTERACT_OBJECT3 = 19     UMETA(DisplayName = "INTERACT_OBJECT3"),
};

USTRUCT(BlueprintType)
struct HOWLOFIRON_API FHI_Requisit
{
	GENERATED_BODY()

public:

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		MissionReq missionType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool completed = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int completionPercentage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int completionNum;

};

UCLASS(BlueprintType)
class HOWLOFIRON_API UHIMission : public UDataAsset
{
	GENERATED_BODY()

public:
	UHIMission() {};
	~UHIMission() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool sequenced;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool oneTimeOnly;



	UPROPERTY(EditAnywhere, meta = (EditInline), BlueprintReadWrite)
		TArray<FHI_Requisit> requisits;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Editable For Debugging")
		bool oneTimeCompleted;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Datatable.h"
#include "GameFramework/Actor.h"
#include "HIPooledObject.generated.h"

UCLASS(Blueprintable)
class HOWLOFIRON_API AHIPooledObject : public AActor
{
	GENERATED_BODY()

public:
	AHIPooledObject();

};

USTRUCT(Blueprintable, BlueprintType)
struct FHI_PooledObject : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UClass* item = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 amount;

};


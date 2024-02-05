// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HIMeshReplacer.generated.h"

UCLASS()
class HOWLOFIRONEDITOR_API AHIMeshReplacer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHIMeshReplacer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(CallInEditor, BlueprintImplementableEvent, Category = "Mesh Replacer", meta = (Tooltip = "Convert static meshes to another static mesh."))
	void ReplaceStaticMeshes();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh Replacer", meta = (ToolTip = "Previous Mesh."))
	UStaticMesh* previousMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh Replacer", meta = (ToolTip = "New Mesh."))
	UStaticMesh* newMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh Replacer", meta = (ToolTip = "New Mesh.", InlineEditConditionToggle))
	bool bUseCustomRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh Replacer", meta = (ToolTip = "New Mesh.", EditCondition = "bUseCustomRotation"))
	FRotator customRotation;
};

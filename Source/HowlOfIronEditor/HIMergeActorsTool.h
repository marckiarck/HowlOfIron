// @AUTHORS: Marco Fernández, Guillermo Suárez
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerBox.h"
#include "HIMergeActorsTool.generated.h"

UENUM()
enum ToolType
{
    InstanceMode,
    MeshFilterMode,
    SelectMode,
    MaterialFilterMode,
    MultipleMeshFilterMode
};

UCLASS()
class HOWLOFIRONEDITOR_API AHIMergeActorsTool : public ATriggerBox
{
    GENERATED_BODY()

public:

    AHIMergeActorsTool(const FObjectInitializer& ObjectInitializer);
    ~AHIMergeActorsTool();

public:
    /*
        InstanceMode -> Create an instanced actors filtering by mesh.
        MeshFilter -> Select all actors inside of the trigger filtering by mesh.
        SelectMode -> Select all actors inside of the trigger.
        MaterialFilterMode -> Select all actors inside of the trigger filtering by material.
        MultipleMeshFilterMode -> Select all actors inside of the trigger filtering by multiple meshes.
    */
    UPROPERTY(EditAnywhere, Category = "Actor Merge Tool")
        TEnumAsByte<ToolType> typeOfTool;

    UPROPERTY(EditAnywhere, Category = "Actor Merge Tool", meta = (EditCondition = "typeOfTool==ToolType::MeshFilterMode || typeOfTool==ToolType::InstanceMode", EditConditionHides))
        UStaticMesh* meshToCompare;

    UPROPERTY(EditAnywhere, Category = "Actor Merge Tool", meta = (EditCondition = "typeOfTool==ToolType::MultipleMeshFilterMode", EditConditionHides))
        TArray<UStaticMesh*> meshesToCompare;

    UPROPERTY(EditAnywhere, Category = "Actor Merge Tool", meta = (EditCondition = "typeOfTool==ToolType::MaterialFilterMode", EditConditionHides))
        UMaterialInterface* materialToFilter;

    // Set true if you want to delete the actors from the map when you instantiate the actors
    UPROPERTY(EditAnywhere, Category = "Actor Merge Tool", meta = (EditCondition = "typeOfTool==ToolType::InstanceMode", EditConditionHides))
        bool destroyOriginalMesh;

protected:

private:
    UPROPERTY(Transient)
        TArray<AStaticMeshActor*> objects;

    UPROPERTY(Transient)
        TArray<UPrimitiveComponent*> primitiveobjects;

public:
    virtual void BeginPlay() override;

    UFUNCTION(CallInEditor, Category = "Actor Merge Tool")
        void HIApplyMode();

protected:

private:
    UFUNCTION()
        void HIInstanceActors();

    UFUNCTION()
        void HIMeshFilter();

    UFUNCTION()
        void HISelectActors();

    UFUNCTION()
        void HIMaterialsFilter();

    UFUNCTION()
        void HIMeshArrayFilter();

    UFUNCTION()
        void HIBoxTraceMultiForObject(TArray<FHitResult>& _auxobjectsInside);

    UFUNCTION()
        void HIClearArrays();
};

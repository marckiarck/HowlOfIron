// @AUTHOR: Germán López

#pragma once

#include "CoreMinimal.h"
#include "CustomActorStyleEnum.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "HICustomActor.generated.h"


USTRUCT(BlueprintType)
struct FCustomActorMesh
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (InlineEditConditionToggle))
        bool useCustomMesh = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (EditCondition = "useCustomMesh"))
        UStaticMesh* mesh = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (InlineEditConditionToggle))
        bool editMeshMaterials = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (EditCondition = "editMeshMaterials"))
        TArray<UMaterial*> materials;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (InlineEditConditionToggle))
        bool editLocationOffset = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (EditCondition = "editLocationOffset"))
        FVector locationOffset = FVector(0.f, 0.f, 0.f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (InlineEditConditionToggle))
        bool editRotationOffset = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (EditCondition = "editRotationOffset"))
        FRotator rotationOffset = FRotator(0.0f, 0.0f, 0.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (InlineEditConditionToggle))
        bool editScaleOffset = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (EditCondition = "editScaleOffset"))
        FVector scaleOffset = FVector(1.0f, 1.0f, 1.0f);
};

UCLASS()
class HOWLOFIRONEDITOR_API AHICustomActor : public AActor
{
    GENERATED_BODY()

public:
    AHICustomActor();

protected:

#pragma region UE_FUNCTIONS
    virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform& Transform) override;
#pragma endregion 

public:

#pragma region CLASS_IMPLEMENTABLE_EVENTS
    /// <summary>
    /// Replace custom actor by static meshes. (Suitable for a final step.)
    /// </summary>
    UFUNCTION(CallInEditor, BlueprintImplementableEvent, Category = "Custom Actor", meta = (CompactNodeTitle = "Convert Actor to Static Meshes", Tooltip = "Replace custom actor by static meshes. (Suitable for a final step.)", EditConditionHides))
        void ConvertActorToStaticMeshes();

    /// <summary>
    /// Set mesh location to a floor point.
    /// </summary>
    UFUNCTION(CallInEditor, BlueprintImplementableEvent, Category = "Raycast Positioning", meta = (Tooltip = "Set mesh location to a floor point."))
        void SetLocationByRaycast();

    /// <summary>
    /// Randomize mesh components location.
    /// </summary>
    UFUNCTION(CallInEditor, BlueprintImplementableEvent, Category = "Randomization", meta = (Tooltip = "Randomize mesh components location."))
        void RandomizeLocation();

    /// <summary>
    /// Randomize mesh components rotation.
    /// </summary>
    UFUNCTION(CallInEditor, BlueprintImplementableEvent, Category = "Randomization", meta = (Tooltip = "Randomize mesh components rotation."))
        void RandomizeRotation();

    /// <summary>
    /// Randomize mesh components scale.
    /// </summary>
    UFUNCTION(CallInEditor, BlueprintImplementableEvent, Category = "Randomization", meta = (Tooltip = "Randomize mesh components scale."))
        void RandomizeScale();

    /// <summary>
    /// Restore mesh components location to its original value.
    /// </summary>
    UFUNCTION(CallInEditor, BlueprintImplementableEvent, Category = "Randomization", meta = (Tooltip = "Restore mesh components location to its original value."))
        void RestoreLocation();

    /// <summary>
    /// Restore mesh components rotation to its original value.
    /// </summary>
    UFUNCTION(CallInEditor, BlueprintImplementableEvent, Category = "Randomization", meta = (Tooltip = "Restore mesh components rotation to its original value."))
        void RestoreRotation();

    /// <summary>
    /// Restore mesh components scale to its original value.
    /// </summary>
    UFUNCTION(CallInEditor, BlueprintImplementableEvent, Category = "Randomization", meta = (Tooltip = "Restore mesh components scale to its original value."))
        void RestoreScale();
#pragma endregion

#pragma region CUSTOM_ACTOR_VARIABLES

#pragma region MAIN
    /// <summary>
    /// Replicated static mesh.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Actor|Main Settings", meta = (DisplayName = "mesh", ToolTip = "Set mesh."))
        UStaticMesh* replicatedStaticMesh = nullptr;

    /// <summary>
    /// Sets custom actor style. You can select between NONE, ROW, MATRIX & CIRCLE style.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Actor|Main Settings", meta = (ToolTip = "Sets custom actor style. You can select between NONE, ROW, MATRIX & CIRCLE style."))
        TEnumAsByte<ECustomActorStyle> style = ECustomActorStyle::None;

    /// <summary>
    /// Sets number of meshes to instantiate.
    /// </summary>
    /// <exception> Not used when style == None or style == Matrix </exception>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Actor|Main Settings", meta = (ToolTip = "Sets number of meshes to instantiate.", EditCondition = "style != ECustomActorStyle::None && style != ECustomActorStyle::Matrix", EditConditionHides, ClampMin = 2, ClampMax = 100, UIMin = 2, UIMax = 100))
        int numberOfMeshes = 2;

#pragma region MATRIX_STYLE
    /// <summary>
    /// Sets number of meshes to instantiate in X axis column.
    /// </summary>
    /// <exception> Not used when style == None, style == Row or style == Circle </exception>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Actor|Main Settings", meta = (ToolTip = "Sets number of meshes to instantiate in X.", EditCondition = "style == ECustomActorStyle::Matrix", EditConditionHides, ClampMin = 2, ClampMax = 100, UIMin = 2, UIMax = 100))
        int meshesX = 2;

    /// <summary>
    /// Sets number of meshes to instantiate in Y axis row.
    /// </summary>
    /// <exception> Not used when style == None, style == Row or style == Circle </exception>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Actor|Main Settings", meta = (ToolTip = "Sets number of meshes to instantiate in Y.", EditCondition = "style == ECustomActorStyle::Matrix", EditConditionHides, ClampMin = 2, ClampMax = 100, UIMin = 2, UIMax = 100))
        int meshesY = 2;

    /// <summary>
    /// Sets distance between instantiated meshes.
    /// </summary>
    /// <exception> Not used when style == None, style == Row or style == Circle </exception>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Actor|Main Settings", meta = (DisplayName = "Distance Between", ToolTip = "Sets distance between instantiated meshes.", EditCondition = "style == ECustomActorStyle::Matrix", EditConditionHides, ClampMin = 0))
        FVector2D matrixMeshSeparation = FVector2D(200.f, 200.f);
#pragma endregion

#pragma region ROW_STYLE
    /// <summary>
    /// Sets distance between instantiated meshes.
    /// </summary>
    /// <exception> Not used when style == None, style == Matrix or style == Circle </exception>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Actor|Main Settings", meta = (DisplayName = "Distance Between", ToolTip = "Sets distance between instantiated meshes.", EditCondition = "style == ECustomActorStyle::Row", EditConditionHides, ClampMin = 0))
        float meshSeparation = 200.f;
#pragma endregion

#pragma region CIRCLE_STYLE
    /// <summary>
    /// Sets circle inner radius.
    /// </summary>
    /// <exception> Not used when style == None, style == Matrix or style == Row </exception>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Actor|Main Settings", meta = (ToolTip = "Sets circle inner radius.", EditCondition = "style == ECustomActorStyle::Circle", EditConditionHides, ClampMin = 0))
        float innerRadius = 250.f;

    /// <summary>
    /// Sets circle angle.
    /// </summary>
    /// <exception> Not used when style == None, style == Matrix or style == Row </exception>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Actor|Main Settings", meta = (ToolTip = "Sets circle angle.", EditCondition = "style == ECustomActorStyle::Circle", EditConditionHides, ClampMin = 0, ClampMax = 360, UIMin = 0, UIMax = 360))
        float angle = 360.f;
#pragma endregion

    /// <summary>
    /// Allow updating mesh materials in editor.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Actor|Main Settings", meta = (Tooltip = "Allow updating mesh materials in editor.", EditCondition = "style == ECustomActorStyle::None", EditConditionHides))
        bool editMeshMaterials = false;

    /// <summary>
    /// Applied materials to the replicatedStaticMesh.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Actor|Main Settings", meta = (ToolTip = "Sets mesh materials.", EditCondition = "style == ECustomActorStyle::None && editMeshMaterials", EditConditionHides))
        TArray<UMaterial*> meshMaterials;

    /// <summary>
    /// Sets mesh rotation offset.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Actor|Main Settings", meta = (ToolTip = "Sets mesh rotation offset.", EditCondition = "style != ECustomActorStyle::None", EditConditionHides))
        FRotator meshRotationOffset;

    /// <summary>
    /// Allow updating mesh data values in editor.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Actor|Main Settings", meta = (DisplayName = "Modify Mesh Data", ToolTip = "Use custom mesh component data (mesh, material, offset, etc.).", EditCondition = "style != ECustomActorStyle::None", EditConditionHides))
        bool useMeshData = false;

    /// <summary>
    /// Replicated mesh data values.
    /// </summary>
    /// <exception> Not used when useMeshData == false </exception>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Actor|Main Settings", meta = (ToolTip = "Sets meshes data.", EditCondition = "useMeshData", EditConditionHides))
        TArray<FCustomActorMesh> meshData;
#pragma endregion

#pragma region OTHER_SETTINGS
    /// <summary>
    /// When ConvertActorToStaticMeshes is called, edits instanced mesh prefix in editor.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (InlineEditConditionToggle))
        bool editPrefix = false;

    /// <summary>
    /// Mesh prefix when it is instanced.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Actor|Other Settings", meta = (DisplayName = "Subindex", ToolTip = "Static mesh name.", EditCondition = "bEditSubindex"))
        FString customMeshPrefix;

    /// <summary>
    /// When ConvertActorToStaticMeshes is called, uses the mesh name when it is instanced in editor.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Actor|Other Settings", meta = (DisplayName = "Use Mesh Name", ToolTip = "Use mesh name as actor name (index)."))
        bool useMeshName = true;

    /// <summary>
    /// When ConvertActorToStaticMeshes is called, enumerates meshes after being instantiated in editor.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Actor|Other Settings", meta = (DisplayName = "Enumerate Meshes", ToolTip = "Enumerate meshes after being instantiated."))
        bool enumerateMeshes = true;

    /// <summary>
    /// When ConvertActorToStaticMeshes is called, groups meshes after converting the components to static meshes.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Actor|Other Settings", meta = (DisplayName = "Group Meshes", ToolTip = "Group meshes after converting the components to static meshes."))
        bool groupMeshes = true;

    /// <summary>
    /// When ConvertActorToStaticMeshes is called, destroys itself after converting mesh components to static meshes.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Actor|Other Settings", meta = (DisplayName = "Destroy After Converting Meshes", ToolTip = "Auto destroy actor after converting mesh components to static meshes."))
        bool autoDestroy = true;

#pragma endregion

#pragma region RANDOMIZATION
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Randomization|Location", meta = (ToolTip = "Minimal random location."))
        FVector minimalLocation = FVector(-50, -50, 0);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Randomization|Location", meta = (ToolTip = "Maximum random location."))
        FVector maximumLocation = FVector(50, 50, 0);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Randomization|Rotation", meta = (ToolTip = "Minimal random rotation."))
        FRotator minimalRotation = FRotator(0, -50, 0);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Randomization|Rotation", meta = (ToolTip = "Maximum random rotation."))
        FRotator maximumRotation = FRotator(0, 50, 0);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Randomization|Scale", meta = (ToolTip = "Minimal random scale."))
        float minimalScale = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Randomization|Scale", meta = (ToolTip = "Maximum random scale."))
        float maximumScale = 1;

#pragma region READ_ONLY
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Randomization|Read Only"/*, meta = (AllowPrivateAccess = "true")*/)
        TArray<FVector> randomLocations;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Randomization|Read Only"/*, meta = (AllowPrivateAccess = "true")*/)
        TArray<FRotator> randomRotations;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Randomization|Read Only"/*, meta = (AllowPrivateAccess = "true")*/)
        TArray<FVector> randomScales;
#pragma endregion

#pragma region ACTOR_LOCATION
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Raycast Positioning", meta = (ToolTip = "Ray Length.", ClampMin = 0.01f))
        float rayLength = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Raycast Positioning", meta = (ToolTip = "Ray Length.", ClampMin = -1, ClampMax = 1))
        FVector rayDirection = FVector(0, 0, -1);

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Raycast Positioning|Read Only"/*, meta = (AllowPrivateAccess = "true")*/)
        TArray<FVector> raycastLocations;
#pragma endregion

#pragma endregion

#pragma endregion 

#pragma region CLASS_FUNCTIONS
    UFUNCTION(/*CallInEditor, */BlueprintCallable, Category = "Custom Actor", meta = (CompactNodeTitle = "Finish Placement", Tooltip = "Static Meshes converted. Destroy custom actor.", EditCondition = "autoDestroyer", EditConditionHides))
        void FinishPlacement();
#pragma endregion

private:

#pragma region CUSTOM_ACTOR_READONLY_VARIABLES
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Custom Actor|Read Only", meta = (AllowPrivateAccess = "true"))
        TArray<UStaticMeshComponent*> components;
#pragma endregion

public:
    /// <summary>
    /// Replace custom actor by static meshes. (Suitable for a final step.)
    /// </summary>
    UFUNCTION(BlueprintCallable, Category = "Custom Actor")
        void HISetActorName(AActor* actor, FString _name);
};



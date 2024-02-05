
// @AUTHORS: Marco Fernández, Guillermo Suárez


#include "HIMergeActorsTool.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/Selection.h"
#include "HowlOfIron/MapLogic/HIInstancedActor.h"
#include "DrawDebugHelpers.h"
#include "HowlOfIron/HIMacros.h"
#include "Kismet/KismetSystemLibrary.h"

AHIMergeActorsTool::AHIMergeActorsTool(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer.DoNotCreateDefaultSubobject(FName("Sprite")))
{
    PrimaryActorTick.bCanEverTick = false;

    destroyOriginalMesh = false;
}

AHIMergeActorsTool::~AHIMergeActorsTool()
{
    meshesToCompare.Empty();
    HIClearArrays();
}

void AHIMergeActorsTool::BeginPlay()
{
    Super::BeginPlay();
    Destroy();
}

void AHIMergeActorsTool::HIInstanceActors()
{
    TArray<FHitResult> auxobjectsInside;
    HIBoxTraceMultiForObject(auxobjectsInside);

    for (FHitResult iter : auxobjectsInside)
    {
        AStaticMeshActor* actormesh = Cast<AStaticMeshActor>(iter.GetActor());
        if (actormesh)
        {
            if (actormesh->GetStaticMeshComponent()->GetStaticMesh() == meshToCompare)
            {
                objects.Add(actormesh);
                primitiveobjects.Add(actormesh->GetStaticMeshComponent());
                GEditor->SelectActor(actormesh, true, true, true);
            }
        }
    }

    if (objects.Num() != 0)
    {
        FActorSpawnParameters params;
        params.OverrideLevel = GetLevel();

        AHIInstancedActor* HIInstancedActor = GetWorld()->SpawnActor<AHIInstancedActor>(FVector::ZeroVector, FRotator::ZeroRotator, params);

        UInstancedStaticMeshComponent* comp = HIInstancedActor->HIGetInstancedMeshComponent();
        comp->SetStaticMesh(meshToCompare);

        for (UPrimitiveComponent* iter : primitiveobjects)
        {
            comp->AddInstance(iter->GetComponentTransform());
        }

        if (destroyOriginalMesh)
        {
            for (AStaticMeshActor* iter : objects)
            {
                iter->Destroy();
            }
        }

        GEditor->SelectActor(HIInstancedActor, true, true, true);
    }
}

void AHIMergeActorsTool::HIMeshFilter()
{
    TArray<FHitResult> auxobjectsInside;
    HIBoxTraceMultiForObject(auxobjectsInside);

    for (FHitResult iter : auxobjectsInside)
    {
        AStaticMeshActor* actormesh = Cast<AStaticMeshActor>(iter.GetActor());
        if (actormesh)
        {
            if (actormesh->GetStaticMeshComponent()->GetStaticMesh() == meshToCompare)
            {
                objects.Add(actormesh);
                primitiveobjects.Add(actormesh->GetStaticMeshComponent());
                GEditor->SelectActor(actormesh, true, true, true);
            }
        }
    }
}

void AHIMergeActorsTool::HISelectActors()
{
    TArray<FHitResult> auxobjectsInside;
    HIBoxTraceMultiForObject(auxobjectsInside);

    for (FHitResult iter : auxobjectsInside)
    {
        AStaticMeshActor* actormesh = Cast<AStaticMeshActor>(iter.GetActor());
        if (actormesh)
        {
            objects.Add(actormesh);
            primitiveobjects.Add(actormesh->GetStaticMeshComponent());
            GEditor->SelectActor(actormesh, true, true, true);
        }
    }
}

void AHIMergeActorsTool::HIMaterialsFilter()
{
    bool validate = false;
    TArray<FHitResult> auxobjectsInside;
    HIBoxTraceMultiForObject(auxobjectsInside);

    for (FHitResult iter : auxobjectsInside)
    {
        AStaticMeshActor* actormesh = Cast<AStaticMeshActor>(iter.GetActor());
        if (actormesh)
        {
            for (int32 i = 0; i < actormesh->GetStaticMeshComponent()->GetMaterials().Num(); ++i)
            {
                if (actormesh->GetStaticMeshComponent()->GetMaterial(i) == materialToFilter)
                {
                    validate = true;
                    break;
                }
            }
        }

        if (validate)
        {
            objects.Add(actormesh);
            primitiveobjects.Add(actormesh->GetStaticMeshComponent());
            GEditor->SelectActor(actormesh, true, true, true);
            validate = false;
        }
    }
}

void AHIMergeActorsTool::HIMeshArrayFilter()
{
    TArray<FHitResult> auxobjectsInside;
    HIBoxTraceMultiForObject(auxobjectsInside);

    for (FHitResult iter : auxobjectsInside)
    {
        AStaticMeshActor* actormesh = Cast<AStaticMeshActor>(iter.GetActor());
        if (actormesh)
        {
            for (UStaticMesh* actors : meshesToCompare)
            {
                if (actormesh->GetStaticMeshComponent()->GetStaticMesh() == actors)
                {
                    objects.Add(actormesh);
                    primitiveobjects.Add(actormesh->GetStaticMeshComponent());
                    GEditor->SelectActor(actormesh, true, true, true);
                }
            }
        }
    }
}

void AHIMergeActorsTool::HIApplyMode()
{
    USelection* selectedActors = GEditor->GetSelectedActors();
    selectedActors->Deselect(this);

    switch (typeOfTool)
    {
    case ToolType::InstanceMode:
    {
        HIInstanceActors();
    }
    break;
    case ToolType::MeshFilterMode:
    {
        HIMeshFilter();
    }
    break;
    case ToolType::SelectMode:
    {
        HISelectActors();
    }
    break;
    case ToolType::MaterialFilterMode:
    {
        HIMaterialsFilter();
    }
    break;
    case ToolType::MultipleMeshFilterMode:
    {
        HIMeshArrayFilter();
    }
    break;
    default:

        break;
    }

    HIClearArrays();
}

void AHIMergeActorsTool::HIBoxTraceMultiForObject(TArray<FHitResult>& _auxobjectsInside)
{
    FVector originPos;
    FVector extendBox;
    GetActorBounds(false, originPos, extendBox);
    TArray<AActor*> actorsignore;
    TArray<TEnumAsByte<EObjectTypeQuery>> objectType;
    objectType.Add(EObjectTypeQuery::ObjectTypeQuery1);

    UKismetSystemLibrary::BoxTraceMultiForObjects(GetWorld(), originPos, originPos, extendBox, GetActorRotation(), objectType, false, actorsignore, EDrawDebugTrace::None, _auxobjectsInside, true, FLinearColor::Transparent, FLinearColor::Transparent, 0.f);


    TArray<FHitResult> newObjects;

    for (FHitResult it : _auxobjectsInside)
    {
        AStaticMeshActor* actormesh = Cast<AStaticMeshActor>(it.GetActor());

        if (actormesh && !actormesh->IsHiddenEd())
        {
            newObjects.Add(it);
        }
    }
    _auxobjectsInside = newObjects;

}

void AHIMergeActorsTool::HIClearArrays()
{
    objects.Empty();
    primitiveobjects.Empty();
}
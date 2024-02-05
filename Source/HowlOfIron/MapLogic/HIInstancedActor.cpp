// @AUTHORS: Marco Fernández, Guillermo Suárez
#include "MapLogic/HIInstancedActor.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/Selection.h"
//#include "Editor.h"
#include "Kismet/KismetSystemLibrary.h"


AHIInstancedActor::AHIInstancedActor()
{
    PrimaryActorTick.bCanEverTick = false;
    instancedstaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponent"));
    SetRootComponent(instancedstaticMeshComponent);
    instancedstaticMeshComponent->SetMobility(EComponentMobility::Static);
}

// Called when the game starts or when spawned
void AHIInstancedActor::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AHIInstancedActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

UInstancedStaticMeshComponent* AHIInstancedActor::HIGetInstancedMeshComponent()
{
    return instancedstaticMeshComponent;
}

void AHIInstancedActor::DesInstacianeitor()
{
    //     USelection* selectedActors = GEditor->GetSelectedActors();
    //     selectedActors->Deselect(this);

    int32 iterNum = instancedstaticMeshComponent->GetInstanceCount();

    TArray<FTransform> arrayTransform;

    //for (int32 i : iterNum)
    for (int32 i = 0; i <= iterNum - 1; ++i)
    {
        FTransform trans;

        if (instancedstaticMeshComponent->GetInstanceTransform(i, trans))
        {

            bool canSpawn = true;

            for (FTransform iterTrans : arrayTransform)
            {
                if (trans.Equals(iterTrans))
                {
                    canSpawn = false;
                    break;
                }
            }


            if (canSpawn)
            {
                FActorSpawnParameters params;
                //UWorld* cos = GetWorld();
                //params.OverrideLevel = this->GetLevel();
                params.Owner = this;
                AStaticMeshActor* punter = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), trans, params);
                arrayTransform.Add(trans);
                punter->GetStaticMeshComponent()->SetStaticMesh(instancedstaticMeshComponent->GetStaticMesh());
                AActor* punter2 = Cast<AActor>(punter);
                // GEditor->SelectActor(punter2, true, true, true); 
                
            }
        }
    }

    Destroy();
}


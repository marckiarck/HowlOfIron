// @AUTHOR: Carlos Fernandez


#include "HowlOfIronEditor.h"
#include "HIEDComponentVisualizer.h"
#include "HowlOfIron/MapLogic/HIComponentVisualizer.h"
#include "UnrealEd.h"

IMPLEMENT_GAME_MODULE(FHowlOfIronEditorModule, HowlOfIronEditor)

void FHowlOfIronEditorModule::CommandSetLodGroups(const TArray<FString>& Params, UWorld* World)
{
	TArray<AActor*> allMeshes;
	UGameplayStatics::GetAllActorsOfClass(World, UStaticMesh::StaticClass(), allMeshes);
	TArray<AActor*> allMeshComponents;
	UGameplayStatics::GetAllActorsOfClass(World, UStaticMeshComponent::StaticClass(), allMeshComponents);

	TArray<AActor*> allActors;
	UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), allActors);

	UE_LOG(LogTemp, Display, TEXT("** Setting lod groups.. **"));

	int numMeshesFixed = 0;
	for (AActor* actor : allActors)
	{
		TArray<UActorComponent*> actorComponents;
		actor->GetComponents(UStaticMeshComponent::StaticClass(), actorComponents);
		for (UActorComponent* actorComponent : actorComponents)
		{
			UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>(actorComponent);
			if (meshComponent)
			{
				UStaticMesh* staticMesh = meshComponent->GetStaticMesh();
				if (staticMesh)
				{
					float numlods = staticMesh->GetNumLODs();
					if (staticMesh->GetNumLODs() <= 1)
					{
						float radius = staticMesh->GetBounds().SphereRadius;
						FName lodGroup = (radius > 300) ? "LargeProp" : "SmallProp"; // Small/large radius threshold is 300, somewhat arbitrary
						staticMesh->SetLODGroup(lodGroup);
						UE_LOG(LogTemp, Display, TEXT("Setting lod group %s to mesh %s"), *lodGroup.ToString() , *staticMesh->GetName());
						++numMeshesFixed;
					}
				}
			}
		}
	}
	UE_LOG(LogTemp, Display, TEXT("** Num meshes fixed: %d **"), numMeshesFixed);
}

void FHowlOfIronEditorModule::CommandSetLightMapResolution(const TArray<FString>& Params, UWorld* World)
{
	if (Params.Num() != 1)
	{
		return;
	}

	int32 lightMapResolution = FCString::Atoi(*Params[0]);

	TArray<AActor*> allMeshes;
	UGameplayStatics::GetAllActorsOfClass(World, UStaticMesh::StaticClass(), allMeshes);
	TArray<AActor*> allMeshComponents;
	UGameplayStatics::GetAllActorsOfClass(World, UStaticMeshComponent::StaticClass(), allMeshComponents);

	TArray<AActor*> allActors;
	UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), allActors);

	UE_LOG(LogTemp, Display, TEXT("** Setting light map resolution %d.. **"), lightMapResolution);

	int numMeshesFixed = 0;
	for (AActor* actor : allActors)
	{
		TArray<UActorComponent*> actorComponents;
		actor->GetComponents(UStaticMeshComponent::StaticClass(), actorComponents);
		for (UActorComponent* actorComponent : actorComponents)
		{
			UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>(actorComponent);
			if (meshComponent)
			{
				UStaticMesh* staticMesh = meshComponent->GetStaticMesh();
				if (staticMesh)
				{
					if (staticMesh->GetLightMapResolution() != lightMapResolution)
					{
						staticMesh->SetLightMapResolution(lightMapResolution);
						staticMesh->MarkPackageDirty();
						UE_LOG(LogTemp, Display, TEXT("Setting light map resolution %d to mesh %s"), lightMapResolution, *staticMesh->GetName());
						++numMeshesFixed;
					}
				}
			}
		}
	}
	UE_LOG(LogTemp, Display, TEXT("** Num meshes fixed: %d **"), numMeshesFixed);
}

void FHowlOfIronEditorModule::StartupModule()
{
	UE_LOG(LogTemp, Display, TEXT("HowlOfIronEditor module has started."));

	if (GUnrealEd)
	{
		TSharedPtr<FHIEDComponentVisualizer> visualizer = MakeShareable(new FHIEDComponentVisualizer());

		if (visualizer.IsValid())
		{
			GUnrealEd->RegisterComponentVisualizer(UHIComponentVisualizer::StaticClass()->GetFName(), visualizer);
			visualizer->OnRegister();
		}
	}

	SetLodGroupsCommand = IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("SetLodGroups"), // Command
		TEXT("Set LOD groups to the meshes of the actual level automatically"), // Command help
		FConsoleCommandWithWorldAndArgsDelegate::CreateRaw(this, &FHowlOfIronEditorModule::CommandSetLodGroups));

	SetLightMapResolutionCommand = IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("SetLightMapResolution"), // Command
		TEXT("Set light map resolution to the meshes of the actual level automatically (SetLightMapResolution <lightMapResolution>)"), // Command help
		FConsoleCommandWithWorldAndArgsDelegate::CreateRaw(this, &FHowlOfIronEditorModule::CommandSetLightMapResolution));
}

void FHowlOfIronEditorModule::ShutdownModule()
{
	UE_LOG(LogTemp, Display, TEXT("HowlOfIronEditor module has shutdown."));

	if (GUnrealEd)
	{
		GUnrealEd->UnregisterComponentVisualizer(UHIComponentVisualizer::StaticClass()->GetFName());
	}
}
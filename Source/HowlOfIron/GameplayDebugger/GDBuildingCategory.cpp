// @AUTHOR: Carlos Fernández


#include "GDBuildingCategory.h"
#include "MapLogic/HIBuilding.h"

#if WITH_GAMEPLAY_DEBUGGER
FGDBuildingCategory::FGDBuildingCategory()
{
    SetDataPackReplication(&DataPack);
}

void FGDBuildingCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
    AHIBuilding* building = Cast<AHIBuilding>(DebugActor);
    if (building)
    {
        DataPack.actorName = DebugActor->GetName();
		FVector buildingCenter;
		FVector buildingExtent;
        building->GetActorBounds(true, buildingCenter, buildingExtent);
        buildingCenter.Z = OwnerPC->GetPawn()->GetActorLocation().Z;
        float distanceToWer = FVector::Dist(buildingCenter, OwnerPC->GetPawn()->GetActorLocation());

        DataPack.distanceToWerewolf = FString::SanitizeFloat(distanceToWer);
        DataPack.height = FString::SanitizeFloat(buildingExtent.Z * 2.f);

    }
}

void FGDBuildingCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
    if (!DataPack.actorName.IsEmpty())
    {
        CanvasContext.Printf(TEXT("{blue}[ENEMY NAME                    ->         %s]"), *DataPack.actorName);
        CanvasContext.Printf(TEXT("{cyan}[DISTANCE TO WEREWOLF] {white} == {white}(%s)"), *DataPack.distanceToWerewolf);
        CanvasContext.Printf(TEXT("{cyan}[HEIGHT]               {white} == {white}(%s)"), *DataPack.height);
    }
}

TSharedRef<FGameplayDebuggerCategory> FGDBuildingCategory::MakeInstance()
{
    return MakeShareable(new FGDBuildingCategory());
}

void FGDBuildingCategory::FBuildingParams::Serialize(FArchive& Ar)
{
    Ar << actorName;
    Ar << distanceToWerewolf;
    Ar << height;
}
#endif // WITH_GAMEPLAY_DEBUGGER
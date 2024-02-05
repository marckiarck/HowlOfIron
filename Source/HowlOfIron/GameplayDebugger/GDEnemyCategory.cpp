// @AUTHOR: Guillermo Suárez


#include "GDEnemyCategory.h"
#include "Characters/Enemies/HIEnemy.h"
#include "Characters/Enemies/HIEnemyController.h"

#if WITH_GAMEPLAY_DEBUGGER
FGDEnemyCategory::FGDEnemyCategory()
{
    SetDataPackReplication(&DataPack);
}

void FGDEnemyCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
    AHIEnemy* enemy = Cast<AHIEnemy>(DebugActor);
    if (enemy)
    {
        float distTo = FVector::Dist(enemy->GetActorLocation(), OwnerPC->GetPawn()->GetActorLocation());

        DataPack.actorName = DebugActor->GetName();
        DataPack.maxHealth = FString::SanitizeFloat(enemy->HIGetAttributes()->GetmaxHealth());
        DataPack.health = FString::SanitizeFloat(enemy->HIGetAttributes()->Gethealth());
        DataPack.maxFear = FString::SanitizeFloat(enemy->HIGetMaxFear());
        DataPack.fear = FString::SanitizeFloat(enemy->HIGetFear());
        DataPack.speed = FString::SanitizeFloat(enemy->HIGetAttributes()->Getspeed());
        DataPack.detectionValue = FString::SanitizeFloat(enemy->HIGetDetectionValue());
        DataPack.distanceTo = FString::SanitizeFloat(distTo);
    }
}

void FGDEnemyCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
    if (!DataPack.actorName.IsEmpty())
    {
        CanvasContext.Printf(TEXT("{blue}[ENEMY NAME          ->         %s]"), *DataPack.actorName);
        CanvasContext.Printf(TEXT("{cyan}[MAX HEALTH] {white} == {white}(%s)"), *DataPack.health);
        CanvasContext.Printf(TEXT("{cyan}[HEALTH]     {white} == {white}(%s)"), *DataPack.maxHealth);
        CanvasContext.Printf(TEXT("{cyan}[MAX FEAR]   {white} == {white}(%s)"), *DataPack.maxFear);
        CanvasContext.Printf(TEXT("{cyan}[FEAR]       {white} == {white}(%s)"), *DataPack.fear);
        CanvasContext.Printf(TEXT("{cyan}[SPEED]      {white} == {white}(%s)"), *DataPack.speed);
        CanvasContext.Printf(TEXT("{cyan}[DETECTION]  {white} == {white}(%s)"), *DataPack.detectionValue);
        CanvasContext.Printf(TEXT("{cyan}[DIST TO]    {white} == {white}(%s)"), *DataPack.distanceTo);
    }
}

TSharedRef<FGameplayDebuggerCategory> FGDEnemyCategory::MakeInstance()
{
    return MakeShareable(new FGDEnemyCategory());
}

void FGDEnemyCategory::FAbilitySys::Serialize(FArchive& Ar)
{
    Ar << actorName;
    Ar << maxHealth;
    Ar << health;
    Ar << maxFear;
    Ar << fear;
    Ar << speed;
    Ar << detectionValue;
    Ar << distanceTo;
}
#endif // WITH_GAMEPLAY_DEBUGGER
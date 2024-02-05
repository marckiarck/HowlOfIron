// @AUTHORS: Guillermo Suárez, Marco Fernández


#include "GDAbilitiesCategory.h"
#include "Characters/VincentVolk/HIWerewolf.h"
#include "Characters/Enemies/HIEnemyController.h"
#include "Characters/Enemies/HIEnemy.h"

#if WITH_GAMEPLAY_DEBUGGER

FGDAbilitiesCategory::FGDAbilitiesCategory()
{
    SetDataPackReplication(&DataPack);
}

void FGDAbilitiesCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{


    if (OwnerPC)
    {
        AHIWerewolf* player = OwnerPC->GetPawn<AHIWerewolf>();
        if (player)
        {
            DataPack.actorName = OwnerPC->GetPawn()->GetName();
            DataPack.maxHealth = FString::SanitizeFloat(player->HIGetAttributes()->GetmaxHealth());
            DataPack.health = FString::SanitizeFloat(player->HIGetAttributes()->Gethealth());
            DataPack.armour = FString::SanitizeFloat(player->HIGetAttributes()->Getarmour());
            DataPack.damage1 = FString::SanitizeFloat(player->HIGetAttributes()->Getdamage1());
            DataPack.damage2 = FString::SanitizeFloat(player->HIGetAttributes()->Getdamage2());
            DataPack.speed = FString::SanitizeFloat(player->HIGetAttributes()->Getspeed());
            DataPack.run = FString::SanitizeFloat(player->HIGetAttributes()->Getrun());
            DataPack.rage = FString::SanitizeFloat(player->HIGetAttributes()->GetchargedValue());
            DataPack.howl = FString::SanitizeFloat(player->HIGetAttributes()->Gethowl());
        }
    }
}

void FGDAbilitiesCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{

    if (!DataPack.actorName.IsEmpty())
    {
        CanvasContext.Printf(TEXT("{blue}[ACTOR NAME         ->         %s]"), *DataPack.actorName);
        CanvasContext.Printf(TEXT("{cyan}[MAX HEALTH]{white} == {white}(%s)"), *DataPack.maxHealth);
        CanvasContext.Printf(TEXT("{cyan}[HEALTH]    {white} == {white}(%s)"), *DataPack.health);
        CanvasContext.Printf(TEXT("{cyan}[ARMOUR]    {white} == {white}(%s)"), *DataPack.armour);
        CanvasContext.Printf(TEXT("{cyan}[DAMAGE 1]  {white} == {white}(%s)"), *DataPack.damage1);
        CanvasContext.Printf(TEXT("{cyan}[DAMAGE 2]  {white} == {white}(%s)"), *DataPack.damage2);
        CanvasContext.Printf(TEXT("{cyan}[SPEED]     {white} == {white}(%s)"), *DataPack.speed);
        CanvasContext.Printf(TEXT("{cyan}[RUN]       {white} == {white}(%s)"), *DataPack.run);
        CanvasContext.Printf(TEXT("{cyan}[RAGE]      {white} == {white}(%s)"), *DataPack.rage);
        CanvasContext.Printf(TEXT("{cyan}[HOWL]      {white} == {white}(%s)"), *DataPack.howl);
    }
}

TSharedRef<FGameplayDebuggerCategory> FGDAbilitiesCategory::MakeInstance()
{
    return MakeShareable(new FGDAbilitiesCategory());
}

void FGDAbilitiesCategory::FAbilitySys::Serialize(FArchive& Ar)
{
    Ar << actorName;
    Ar << maxHealth;
    Ar << health;
    Ar << armour;
    Ar << damage1;
    Ar << damage2;
    Ar << speed;
    Ar << run;
    Ar << rage;
    Ar << howl;
}
#endif // WITH_GAMEPLAY_DEBUGGER
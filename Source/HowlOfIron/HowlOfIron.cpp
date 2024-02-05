// @AUTHOR: Guillermo
#include "HowlOfIron.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE(HowlOfIronModule, HowlOfIron, "HowlOfIron");

#if WITH_GAMEPLAY_DEBUGGER
#include "GameplayDebugger.h"
#include "GameplayDebugger/GDAbilitiesCategory.h"
#include "GameplayDebugger/GDEnemyCategory.h"
#include "GameplayDebugger/GDBuildingCategory.h"
#endif // WITH_GAMEPLAY_DEBUGGER

void HowlOfIronModule::StartupModule()
{
#if WITH_GAMEPLAY_DEBUGGER
    IGameplayDebugger& GameplayDebuggerModule = IGameplayDebugger::Get();

    // Vincent Abilities
    GameplayDebuggerModule.RegisterCategory("VincentAbilities", IGameplayDebugger::FOnGetCategory::CreateStatic(&FGDAbilitiesCategory::MakeInstance),
        EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 6);
    GameplayDebuggerModule.NotifyCategoriesChanged();

    // Enemy Abilities
    GameplayDebuggerModule.RegisterCategory("EnemyAbilities", IGameplayDebugger::FOnGetCategory::CreateStatic(&FGDEnemyCategory::MakeInstance),
        EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 7);
    GameplayDebuggerModule.NotifyCategoriesChanged();

    // Building Params
    GameplayDebuggerModule.RegisterCategory("BuildingParams", IGameplayDebugger::FOnGetCategory::CreateStatic(&FGDBuildingCategory::MakeInstance),
        EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 8);
    GameplayDebuggerModule.NotifyCategoriesChanged();
#endif
}

void HowlOfIronModule::ShutdownModule()
{
#if WITH_GAMEPLAY_DEBUGGER
    IGameplayDebugger& GameplayDebuggerModule = IGameplayDebugger::Get();
    GameplayDebuggerModule.UnregisterCategory(TEXT("VincentAbilities"));
    GameplayDebuggerModule.UnregisterCategory(TEXT("EnemyAbilities"));
    GameplayDebuggerModule.UnregisterCategory(TEXT("BuildingParams"));
#endif
}


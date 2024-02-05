// @AUTHOR: Carlos Fernandez

#pragma once

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

class FHowlOfIronEditorModule : public IModuleInterface
{
private:
	IConsoleCommand* SetLodGroupsCommand { nullptr };
	IConsoleCommand* SetLightMapResolutionCommand { nullptr };

	void CommandSetLodGroups(const TArray<FString>& Params, UWorld* World);
	void CommandSetLightMapResolution(const TArray<FString>& Params, UWorld* World);

public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
// @AUTHOR: Guillermo
#pragma once

#include "CoreMinimal.h"

class HowlOfIronModule : public FDefaultGameModuleImpl
{
public:
    // This will get called when the editor loads the module
    virtual void StartupModule() override;
    // This will get called when the editor unloads the module
    virtual void ShutdownModule() override;
};
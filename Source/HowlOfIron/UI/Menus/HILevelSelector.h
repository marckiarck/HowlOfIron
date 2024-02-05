// @AUTHOR: Guillermo Suarez

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HILevelSelector.generated.h"

/**
 * 
 */
UCLASS()
class HOWLOFIRON_API UHILevelSelector : public UUserWidget
{
	GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:


protected:


private:


public:


protected:


private:
};

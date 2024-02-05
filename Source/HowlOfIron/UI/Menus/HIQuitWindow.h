// @AUTHOR: Guillermo Suárez

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HIQuitWindow.generated.h"

UCLASS()
class HOWLOFIRON_API UHIQuitWindow : public UUserWidget
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

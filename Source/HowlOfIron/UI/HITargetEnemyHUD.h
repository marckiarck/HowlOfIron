// @AUTHOR: Guillermo Suarez 
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "HITargetEnemyHUD.generated.h"

UCLASS()
class HOWLOFIRON_API UHITargetEnemyHUD : public UUserWidget
{
   GENERATED_BODY()
public:
   virtual bool Initialize() override;
   virtual void NativePreConstruct() override;
   virtual void NativeConstruct() override;

public:
   UPROPERTY(meta = (BindWidget))
      UImage* targetImage;

protected:


private:


public:
   void HISetTargetImageVisibility(ESlateVisibility _visibility);

protected:


private:


};

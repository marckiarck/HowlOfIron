// @AUTHOR: Carlos

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HIButtonHUDWidget.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHIButtonHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UImage* buttonImage;

protected:
	virtual void NativeConstruct() override;
};

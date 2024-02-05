// @AUTHOR: Guillermo Suárez, Germán López

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SizeBox.h"
#include "Engine/DataTable.h"
#include "HIRowClass.generated.h"

class UHorizontalBox;
class UHITextClass;
class UImage;

UCLASS()
class HOWLOFIRON_API UHIRowClass : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;


public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        USizeBox* rowContainer;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHorizontalBox* settingBox;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHITextClass* settingText;
        
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UImage* selectedRowImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Row Settings|Visual", meta = (InlineEditConditionToggle))
        bool useOverridenWidth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Row Settings|Visual", meta = (ToolTip = "Overrides row width.", EditCondition = "useOverridenWidth", ClampMin = 500, ClampMax = 1920, UIMin = 500, UIMax = 1920))
        float overridenWidth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Row Settings|Visual", meta = (InlineEditConditionToggle))
        bool useCustomTextStyleData;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Row Settings|Visual", meta = (ToolTip = "Edits text style data.", EditCondition = "useCustomTextStyleData"))
        UDataTable* textStyleData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Row Settings|Data", meta = (InlineEditConditionToggle))
        bool useCustomText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Row Settings|Data", meta = (ToolTip = "Sets row setting text.", EditCondition = "useCustomText"))
        FText customText;



protected:


private:


public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void HIFocused();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void HIClearFocus();

protected:


private:


};

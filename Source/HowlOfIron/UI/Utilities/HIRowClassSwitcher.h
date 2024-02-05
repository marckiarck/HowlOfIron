// @AUTHOR: Guillermo Suárez, Germán López
#pragma once

#include "CoreMinimal.h"
#include "HIRowClass.h"
#include "HIRowClassSwitcher.generated.h"

class UHITextSwitcher;

UCLASS()
class HOWLOFIRON_API UHIRowClassSwitcher : public UHIRowClass
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UHITextSwitcher* settingSwitcher;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Row Settings|Visual", meta = (InlineEditConditionToggle))
        bool useSwitchTextStyleData;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Row Settings|Visual", meta = (ToolTip = "Edits switch text style data.", EditCondition = "useCustomTextStyleData"))
        UDataTable* switchTextStyleData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Row Settings|Data", meta = (InlineEditConditionToggle))
        bool useChoices;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Appearance|Row Settings|Data", meta = (ToolTip = "Edits switch selectable choices.", EditCondition = "useChoices"))
        TArray<FText> choices;


protected:


private:


public:


protected:


private:


};

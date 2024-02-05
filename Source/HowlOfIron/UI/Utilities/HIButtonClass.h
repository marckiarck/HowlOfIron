// @AUTHOR: Guillermo Su�rez, Germ�n L�pez

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "HIButtonClass.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHIButtonClass : public UUserWidget
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UButton* customButton;
    // class SButton* butt;
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UHITextClass* customTextButton;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Row Settings|Visual", meta = (InlineEditConditionToggle))
        bool useCustomTextStyleData;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Row Settings|Visual", meta = (ToolTip = "Edits text style data.", EditCondition = "useCustomTextStyleData"))
        UDataTable* textStyleData;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Row Settings|Visual", meta = (ToolTip = "Edits if background is shown."))
        bool showButtonBackground;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Row Settings|Visual", meta = (ToolTip = "Animation index when the button is selected.", ClampMin = 0))
        int selectionAnimationIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Row Settings|Data", meta = (InlineEditConditionToggle))
        bool useButtonText;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Row Settings|Data", meta = (ToolTip = "Edits button text.", EditCondition = "useButtonText"))
        FText buttonText;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Row Settings|Data", meta = (ToolTip = "Edits button index."))
        int buttonIndex;

protected:


private:

public:
    UFUNCTION()
        void HIFocused();

    UFUNCTION()
        void HIClearFocus();

protected:


private:


};

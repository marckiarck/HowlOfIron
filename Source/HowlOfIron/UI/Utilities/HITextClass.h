// @AUTHOR: Guillermo Suárez, Germán López

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "HITextClass.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHITextClass : public UUserWidget
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class URichTextBlock* customRichText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Custom properties", meta = (InlineEditConditionToggle))
        bool useCustomText;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Custom properties", meta = (ToolTip = "Edits custom text.", EditCondition = "useCustomText"))
        FText customText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Custom properties", meta = (InlineEditConditionToggle))
        bool useCustomTextStyleData;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Custom properties", meta = (ToolTip = "Edits text style data.", EditCondition = "useCustomTextStyleData"))
        UDataTable* textStyleData;


protected:


private:


public:
    UFUNCTION(BlueprintCallable)
        void HISetCustomText(FText newText);

    UFUNCTION(BlueprintCallable)
        void HISetCustomTextStyle(UDataTable* newTextStyleData);



protected:


private:


};

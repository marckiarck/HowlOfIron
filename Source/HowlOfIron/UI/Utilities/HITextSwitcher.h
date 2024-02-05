// @AUTHORS: Guillermo Suárez, Germán López

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "HITextSwitcher.generated.h"

/**
 *
 */
UCLASS()
class HOWLOFIRON_API UHITextSwitcher : public UUserWidget
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UButton* leftSwitcher;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UButton* rightSwitcher;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        class UHITextClass* customSwitcherText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Visual", meta = (InlineEditConditionToggle))
        bool useSwitchTextStyleData;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Appearance|Visual", meta = (ToolTip = "Edits switch text style data.", EditCondition = "useCustomTextStyleData"))
        UDataTable* switchTextStyleData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance|Data", meta = (InlineEditConditionToggle))
        bool useChoices;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool canChange;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Appearance|Data", meta = (ToolTip = "Edits switch selectable choices.", EditCondition = "useChoices"))
        TArray<FText> choices;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        int index;

protected:


private:
    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
        int currentIndex;

public:
    UFUNCTION(BlueprintCallable)
        void HISetChoices(TArray<FText> _choices);

    UFUNCTION(BlueprintCallable)
        int HIUpdateIndex(int newIndex);

protected:



private:


};
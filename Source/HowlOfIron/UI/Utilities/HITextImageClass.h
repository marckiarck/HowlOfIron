// @AUTHOR: Guillermo Suárez

#pragma once

#include "CoreMinimal.h"
#include "HITextClass.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "HITextImageClass.generated.h"

UCLASS()
class HOWLOFIRON_API UHITextImageClass : public UHITextClass
{
    GENERATED_BODY()
public:
    virtual bool Initialize() override;
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UBorder* customBorder;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
        UImage* customImage;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        int textImageID;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        TArray<FWidgetTransform> positions; 

protected:


private:


public:


protected:


private:


};

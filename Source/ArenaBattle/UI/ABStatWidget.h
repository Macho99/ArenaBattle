// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABStatWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABStatWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    void NativeConstruct() override;

public:
    void SetStatName(const FString& StatName);
    void SetStat(float BaseValue, float ModifierValue);
    
private:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<class UTextBlock> StatNameText;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<class UTextBlock> BaseStatText;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<class UTextBlock> ModifierStatText;
};

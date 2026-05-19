// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/ABStatWidget.h"
#include "Components/TextBlock.h"

void UABStatWidget::NativeConstruct()
{
    Super::NativeConstruct();
    StatNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("StatNameText")));
    BaseStatText = Cast<UTextBlock>(GetWidgetFromName(TEXT("BaseStatText")));
    ModifierStatText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ModifierStatText")));
}

void UABStatWidget::SetStatName(const FString& StatName)
{
    if (StatNameText)
    {
        StatNameText->SetText(FText::FromString(StatName));
    }
}

void UABStatWidget::SetStat(float BaseValue, float ModifierValue)
{
    if (BaseStatText)
    {
        BaseStatText->SetText(FText::AsNumber(BaseValue));
    }
    if (ModifierStatText)
    {
        ModifierStatText->SetText(FText::AsNumber(ModifierValue));
    }
}
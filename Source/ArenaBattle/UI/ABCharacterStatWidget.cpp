// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABCharacterStatWidget.h"
#include "GameData/ABCharacterStat.h"
#include "Components/TextBlock.h"
#include "UI/ABStatWidget.h"
#include "Components/VerticalBox.h"

void UABCharacterStatWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (!StatWidgetClass)
    {
        UE_LOG(LogTemp, Error, TEXT("StatWidgetClass is not set in %s"), *GetName());
        return;
    }

    UVerticalBox* VerticalBox = Cast<UVerticalBox>(GetWidgetFromName(TEXT("VerticalBox")));

    for (TFieldIterator<FProperty> PropIt(FABCharacterStat::StaticStruct()); PropIt; ++PropIt)
    {
        const FName PropKey(PropIt->GetName());
        UABStatWidget* StatWidget = CreateWidget<UABStatWidget>(GetOwningPlayer(), StatWidgetClass);
        StatWidget->SetStatName(PropKey.ToString());
        VerticalBox->AddChild(StatWidget);
        StatWidgets.Add(StatWidget);
    }
}

void UABCharacterStatWidget::UpdateStat(const FABCharacterStat& BaseStat, const FABCharacterStat& ModifierStat)
{
	int32 StatIdx = 0;
	for (TFieldIterator<FNumericProperty> PropIt(FABCharacterStat::StaticStruct()); PropIt; ++PropIt)
	{
		const FName PropKey(PropIt->GetName());

		float BaseData = 0.0f;
		PropIt->GetValue_InContainer((const void*)&BaseStat, &BaseData);
		float ModifierData = 0.0f;
		PropIt->GetValue_InContainer((const void*)&ModifierStat, &ModifierData);
        StatWidgets[StatIdx]->SetStat(BaseData, ModifierData);
		StatIdx++;
	}
}

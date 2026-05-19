// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABCharacterStatWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABCharacterStatWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    virtual void NativeConstruct() override;

public:
    void UpdateStat(const struct FABCharacterStat& BaseStat, const FABCharacterStat& ModifierStat);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Widgets")
    TSubclassOf<class UABStatWidget> StatWidgetClass;

    UPROPERTY(VisibleAnywhere)
    TArray<TObjectPtr<class UABStatWidget>> StatWidgets;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/ABCharacterStat.h"
#include "ABCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /*CurrentHp*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStatChangedDelegate, const FABCharacterStat& /*Base*/, const FABCharacterStat& /*Modifier*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENABATTLE_API UABCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UABCharacterStatComponent();

protected:
    virtual void InitializeComponent() override;	

public:
    FOnHpZeroDelegate OnHpZero;
    FOnHpChangedDelegate OnHpChanged;
    FOnStatChangedDelegate OnStatChanged;

    void SetLevelStat(int32 InNewLevel);
    FORCEINLINE float GetCurrentLevel() const { return CurrentLevel; }
    FORCEINLINE void AddBaseStat(const FABCharacterStat& InAddedBaseStat) { BaseStat = BaseStat + InAddedBaseStat; OnStatChanged.Broadcast(BaseStat, ModifierStat); }
    FORCEINLINE void SetBaseStat(const FABCharacterStat& InBaseStat) { BaseStat = InBaseStat; OnStatChanged.Broadcast(BaseStat, ModifierStat); }
    FORCEINLINE void SetModifierStat(const FABCharacterStat& InModifierStat) { ModifierStat = InModifierStat; OnStatChanged.Broadcast(BaseStat, ModifierStat); }
    FORCEINLINE const FABCharacterStat& GetBaseStat() const { return BaseStat; }
    FORCEINLINE const FABCharacterStat& GetModifierStat() const { return ModifierStat; }
    FORCEINLINE FABCharacterStat GetTotalStat() const { return BaseStat + ModifierStat; }
    FORCEINLINE void HealHp(float InHealAmount) { SetHp(CurrentHp + InHealAmount); }
    FORCEINLINE float GetCurrentHp() const { return CurrentHp; }
    FORCEINLINE float GetAttackRadius() const { return AttackRadius; }
    float ApplyDamage(float InDamage);

protected:
	void SetHp(float NewHp);

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentLevel;

	UPROPERTY(VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	float AttackRadius;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FABCharacterStat BaseStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FABCharacterStat ModifierStat;
};

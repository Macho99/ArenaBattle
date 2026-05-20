// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ABPlayerController.h"
#include "UI/ABHUDWidget.h"
#include "Player/ABSaveGame.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogABPlayerController);

AABPlayerController::AABPlayerController()
{
	static ConstructorHelpers::FClassFinder<UABHUDWidget> ABHUDWidgetRef(TEXT("/Game/ArenaBattle/UI/WBP_ABHUD.WBP_ABHUD_C"));
	if (ABHUDWidgetRef.Class)
	{
		ABHUDWidgetClass = ABHUDWidgetRef.Class;
	}
}

void AABPlayerController::GameScoreChanged(int32 NewScore)
{
    K2_OnScoreChanged(NewScore);
    UE_LOG(LogTemp, Log, TEXT("Score Changed: %d"), NewScore);
}

void AABPlayerController::GameClear()
{
	K2_OnGameClear();
}

void AABPlayerController::GameOver()
{
    K2_OnGameOver();

    if (!UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Player0"), 0))
    {
        UE_LOG(LogABPlayerController, Error, TEXT("Failed to save game."));
    }
    K2_OnGameRetryCount(SaveGameInstance->RetryCount);
    UE_LOG(LogABPlayerController, Log, TEXT("Retry Count: %d"), SaveGameInstance->RetryCount);
}

void AABPlayerController::BeginPlay()
{
    Super::BeginPlay();

    FInputModeGameOnly GameOnlyInputMode;
    SetInputMode(GameOnlyInputMode);

    SaveGameInstance = Cast<UABSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Player0"), 0));
    if (SaveGameInstance)
    {
        SaveGameInstance->RetryCount++;
    }
    else
    {
        SaveGameInstance = NewObject<UABSaveGame>();
    }

    K2_OnGameRetryCount(SaveGameInstance->RetryCount);
    UE_LOG(LogABPlayerController, Log, TEXT("Retry Count: %d"), SaveGameInstance->RetryCount);
}

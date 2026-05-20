// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ABGameMode.h"
#include "Player/ABPlayerController.h"

AABGameMode::AABGameMode()
{
    //static ConstructorHelpers::FClassFinder<APawn> ThirdPersonClassRef(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C"));
    //if (ThirdPersonClassRef.Class)
    //{
    //    DefaultPawnClass = ThirdPersonClassRef.Class;
    //}

    static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Game/ArenaBattle/Blueprint/BP_ABCharacterPlayer.BP_ABCharacterPlayer_C"));
    if (DefaultPawnClassRef.Class)
    {
        DefaultPawnClass = DefaultPawnClassRef.Class;
    }

    static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Game/ArenaBattle/Blueprint/BP_ABPlayerController.BP_ABPlayerController_C"));
    if (PlayerControllerClassRef.Class)
    {
        PlayerControllerClass = PlayerControllerClassRef.Class;
    }

    ClearScore = 3;
    CurrentScore = 0;
    bIsCleared = false;
}

void AABGameMode::OnPlayerScoreChanged(int32 NewPlayerScore)
{
    CurrentScore = NewPlayerScore;
    AABPlayerController* ABPlayerController = Cast<AABPlayerController>(GetWorld()->GetFirstPlayerController());
    if (ABPlayerController)
    {
        ABPlayerController->GameScoreChanged(CurrentScore);
    }

    if (CurrentScore >= ClearScore)
    {
        bIsCleared = true;    
        if (ABPlayerController)
        {
            ABPlayerController->GameClear();
        }
    }
}

void AABGameMode::OnPlayerDead()
{
    AABPlayerController* ABPlayerController = Cast<AABPlayerController>(GetWorld()->GetFirstPlayerController());
    if (ABPlayerController)
    {
        ABPlayerController->GameOver();
    }
}

bool AABGameMode::IsGameCleared()
{
    return bIsCleared;
}

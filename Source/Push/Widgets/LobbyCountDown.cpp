#include "Widgets/LobbyCountDown.h"
#include "Kismet/KismetTextLibrary.h"
#include "Components/TextBlock.h"
#include "GameState/LobbyGameState.h"
#include "Kismet/GameplayStatics.h"

void ULobbyCountDown::UpdateWidget()
{
    PlayerAmount->SetText(FText::FromString(FString::FromInt(NumofPlayers) + FString(" / 3 players")));
    CountDown->SetText(FText::FromString(FString::FromInt(Countdown) + FString(" seconds")));
}

void ULobbyCountDown::SetPlayerNum(int InNum)
{
    NumofPlayers = InNum;
    UpdateWidget();
}

void ULobbyCountDown::SetCountdown(int InNum)
{
    Countdown = InNum;
    UpdateWidget();
}


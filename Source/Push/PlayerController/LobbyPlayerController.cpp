#include "PlayerController/LobbyPlayerController.h"
#include "Global.h"
#include "Character/PushCharacter.h"
#include "Components/WidgetComponent.h"
#include "GameInstance/PushGameInstance.h"
#include "GameMode/LobbyGameMode.h"
#include "GameState/LobbyGameState.h"
#include "HUD/LobbyHUD.h"
#include "Widgets/LobbyCountDown.h"
#include "Widgets/LobbyReadyButton.h"
#include "Widgets/LobbyReadyState.h"

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	LobbyHUD = Cast<ALobbyHUD>(GetHUD());

	if (IsValid(LobbyHUD))
	{
		LobbyHUD->AddWidget();
		if (LobbyHUD->CheckWidget("LobbyCountDown"))
		{
			LobbyHUD->GetWidget<ULobbyCountDown>("LobbyCountDown")->SetVisibility(ESlateVisibility::Visible);
			ALobbyGameState* state = Cast<ALobbyGameState>(UGameplayStatics::GetGameState(GetWorld()));
			if (state != nullptr)
				LobbyHUD->GetWidget<ULobbyCountDown>("LobbyCountDown")->SetPlayerNum(state->NumofPlayers);
		}
	}

	LobbyGameMode = Cast<ALobbyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	SetUpLobbyInfo();
}

void ALobbyPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//SetHUDCountdownTime(); // LobbyHUD의 함수 UpdateWidget()으로 '입장한 플레이어 & 시간' 업데이트 
}

void ALobbyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}

void ALobbyPlayerController::OnReadyButton_Clicked_Implementation()
{
	OnReadyButton_Clicked_Server();
}

void ALobbyPlayerController::OnReadyButton_Clicked_Server_Implementation()
{
	PlayerLobbyData.bReady = !PlayerLobbyData.bReady;

	if (LobbyGameMode)
	{
		LobbyGameMode->UpdateLobbyInfo(this);
	}

}

void ALobbyPlayerController::SetPlayerName_Server_Implementation(const FString& InPlayerName)
{
	PlayerLobbyData.PlayerName = InPlayerName;

	if (LobbyGameMode)
	{
		LobbyGameMode->UpdateLobbyInfo(this);
	}
}

void ALobbyPlayerController::SetUpLobbyInfo_Implementation()
{
	if (IsLocalPlayerController())
	{
		SetShowMouseCursor(true);

		FInputModeGameAndUI InputMode;
		InputMode.SetHideCursorDuringCapture(false);

		SetInputMode(InputMode);

		LobbyReadyButton = CreateWidget<ULobbyReadyButton>(this, ReadyButton, "ReadyButton");
		LobbyReadyButton->AddToViewport();

		UPushGameInstance* gameInstance = Cast<UPushGameInstance>(GetGameInstance());
		if (gameInstance)
		{
			SetPlayerName_Server(gameInstance->GetPlayerName());
		}
	}
}

void ALobbyPlayerController::TryAgainUpdatingLobbyInfo_Implementation()
{

}

void ALobbyPlayerController::UpdateTimer_Client_Implementation(int InTime)
{
	if (LobbyHUD->CheckWidget("LobbyCountDown"))
	{
		LobbyHUD->GetWidget<ULobbyCountDown>("LobbyCountDown")->SetCountdown(InTime);
	}
}

void ALobbyPlayerController::UpdatePlayerNum_Client_Implementation(int InNum)
{
	if (LobbyHUD == nullptr)
	{
		CLog::Log("HUD invalid");
		return;
	}

	if (LobbyHUD->CheckWidget("LobbyCountDown"))
	{
		LobbyHUD->GetWidget<ULobbyCountDown>("LobbyCountDown")->SetPlayerNum(InNum);
	}
	else
	{
		CLog::Log("No Widget");
	}
}


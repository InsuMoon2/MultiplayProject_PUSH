#include "GameMode/LobbyGameMode.h"

#include "Character/PushCharacter.h"
#include "GameFramework/GameState.h"
#include "GameState/LobbyGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Objects/LobbyPlayerPlatform.h"
#include "PlayerController/LobbyPlayerController.h"
#include "Utilites/CLog.h"
#include "Widgets/LobbyCountDown.h"
#include "Global.h"
#include "Components/WidgetComponent.h"
#include "Widgets/LobbyReadyButton.h"
#include "Widgets/LobbyReadyState.h"

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();

}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	NumOfPlayers++;

	if (false == IsValid(NewPlayer)) return;

	ALobbyGameState* lobbyGameState = GetGameState<ALobbyGameState>();

	if (lobbyGameState == nullptr)
	{
		CLog::Log("GameState Nullptr");
		return;
	}

	lobbyGameState->PlayerConnection(NumOfPlayers);

	AllPC.Add(NewPlayer);

}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	ALobbyGameState* lobbyGameState = GetGameState<ALobbyGameState>();

	AllPC.Empty();
}

void ALobbyGameMode::PlayerLoginInServer_Implementation()
{
	NumOfPlayers++;
}

void ALobbyGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ALobbyGameMode::CountDown()
{
	ALobbyGameState* lobbyGameState = GetGameState<ALobbyGameState>();

	if (lobbyGameState != nullptr)
	{
		lobbyGameState->CountDown(countdownTimer);
	}

	countdownTimer--;

	if (countdownTimer < 0)
	{
		EnterMap();
	}
}

void ALobbyGameMode::EnterMap()
{
	TWeakObjectPtr<UWorld> World = GetWorld();
	if (World.IsValid())
	{
		//World->ServerTravel(FString("/Game/SW/Maps/TestLevelMap"));
		World->ServerTravel(FString("/Game/Maps/MainMap"));
		CLog::Log("Dedicated Server entered MainMap!!");
	}
}

void ALobbyGameMode::UpdateLobbyInfo(APlayerController* InPlayerController)
{
	for (ALobbyPlayerPlatform* lobbyInfo : LobbyPlatforms)
	{
		if (lobbyInfo->PlayerController == InPlayerController)
		{
			APushCharacter* pushCharacter = Cast<APushCharacter>(lobbyInfo->CurrentCharacter);
			if (pushCharacter)
			{
				ALobbyPlayerController* lobbyPlayerController = Cast<ALobbyPlayerController>(InPlayerController);
				if (lobbyPlayerController)
				{
					FLobbyData lobbyData;

					lobbyData.PlayerController = InPlayerController;
					lobbyData.PlayerName = lobbyPlayerController->PlayerLobbyData.PlayerName;
					lobbyData.bReady = lobbyPlayerController->PlayerLobbyData.bReady;

					pushCharacter->UpdatePlayerLobbyInfo(lobbyData);
					OnCheckPlayerAllReady();

					return;
				}
			}
		}
	}
	// 제대로 값이 안들어왔을 때 다시 실행 (동기화 문제)
	ALobbyPlayerController* lobbyPlayerController = Cast<ALobbyPlayerController>(InPlayerController);
	if (lobbyPlayerController)
	{
		lobbyPlayerController->TryAgainUpdatingLobbyInfo();
	}
	
}

void ALobbyGameMode::OnCheckPlayerAllReady_Implementation()
{
	// 모든 플레이어가 준비되었는지 확인
	bAllPlayerReady = true;

	for (APlayerController* playerController : AllPC)
	{
		ALobbyPlayerController* lobbyController = Cast<ALobbyPlayerController>(playerController);
		if (lobbyController)
		{
			if (lobbyController->PlayerLobbyData.bReady == false)
			{
				bAllPlayerReady = false;
			}
		}
	}

	if (bAllPlayerReady == true)
	{
		if (HasAuthority())
		{
			TWeakObjectPtr<UGameInstance> GameInstance = GetGameInstance();
			if (GameInstance.IsValid())
			{
				countdownTimer = StartCountdown;
				GetWorld()->GetTimerManager().SetTimer(LobbyTimeHandle, this, &ALobbyGameMode::CountDown, 1.0f, true, 0);
			}
		}
	}
}

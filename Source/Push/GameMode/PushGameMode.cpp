#include "PushGameMode.h"
#include "Character/PushCharacter.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "PlayerController/PushPlayerController.h"
#include "GameState/PushGameState.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Utilites/CLog.h"
#include "Global.h"
#include "Components/ResourceComponent.h"
#include "Components/StateComponent.h"
#include "Objects/Ring.h"
#include "Widgets/MainUI.h"
#include "HUD/MainHUD.h"

namespace MatchState
{
	const FName Round = FName("Round"); 
}

namespace MatchState
{
	const FName Result = FName("Result"); // 결과발표. 내장되지 않은 MatchState을 사용시 명시해서 사용
}

namespace MatchState
{
	const FName TotalResult = FName("TotalResult"); // 최종 결과 발표
}

APushGameMode::APushGameMode()
{
	bDelayedStart = true; // 캐릭터가 시작부터 끝까지 계속 스폰되어 있어야하므로 MatchState::WaitingToStart를 없애고 bDelayedStart = true로 변경하였다.
	
}

void APushGameMode::BeginPlay()
{
	Super::BeginPlay();

	tempTime = GetWorld()->GetTimeSeconds();
	CountdownTime = WarmupTime;
	CurrentTime = 0.0f;

	PushGameState = Cast<APushGameState>(GameState);

	if(PushGameState == nullptr){ // 예외처리
		CLog::Log("pushGameState == nullptr !!");
		return;
	}

	TWeakObjectPtr<UWorld> world = GetWorld();

	if (world.IsValid())
	{
		if (IsValid(RingClass))
		{
			Ring = world->SpawnActor<ARing>(RingClass);
			Ring->SetActorLocation(FVector(-45800.f, 15700.f, -24000.f));
		}
	}

	OnRoundEnd.AddDynamic(this, &APushGameMode::RoundEnd);
	OnRoundStart.AddDynamic(this, &APushGameMode::RoundStart);
}


void APushGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	PushGameState->SetTime(CurrentTime);
	if (MatchState == MatchState::InProgress) // 상점
	{
		CurrentTime = (CountdownTime - (GetWorld()->GetTimeSeconds() - tempTime));
		if (CurrentTime <= 0.0f)
		{
			CountdownTime = RoundTime[Round];
			tempTime = GetWorld()->GetTimeSeconds();

			if (OnRoundStart.IsBound())
				OnRoundStart.Broadcast();

			SetMatchState(MatchState::Round);
		}
	}
	else if (MatchState == MatchState::Round) // 라운드s
	{
		CurrentTime = (CountdownTime - (GetWorld()->GetTimeSeconds() - tempTime));
		if (CurrentTime <= 0.0f)
		{
			if (RoundTime.Num() - 1 <= Round)
			{
				tempTime = GetWorld()->GetTimeSeconds();
				CountdownTime = ResultTime;
				Round = 0;

				if (Games >= TotalNumOfGames)
				{
					SetMatchState(MatchState::TotalResult);
					PushGameState->ShowTotalRank();
					SetActorTickEnabled(false);
					CurrentTime = 0.0f;
					return;
				}

				SetMatchState(MatchState::Result); // 결과발표
			}
			else
			{
				if (Ring.Get() != nullptr)
					Ring.Get()->Shrink(RingRadius[Round], ShrinkRate);

				CountdownTime = RoundTime[++Round];
				tempTime = GetWorld()->GetTimeSeconds();
			}
		}
	}
	else if (MatchState == MatchState::Result) // 결과발표
	{
		CurrentTime = (CountdownTime - (GetWorld()->GetTimeSeconds() - tempTime));
		if (CurrentTime <= 0.0f)
		{
			tempTime = GetWorld()->GetTimeSeconds();
			CountdownTime = WarmupTime;
			if (OnRoundEnd.IsBound() == true)
				OnRoundEnd.Broadcast();
			SetMatchState(MatchState::InProgress);
		}
	}
}

void APushGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	APushPlayerController* controller = Cast<APushPlayerController>(NewPlayer);

	if (controller == nullptr)
		return;

	APushCharacter* character = Cast<APushCharacter>(controller->GetPawn());

	if (character == nullptr)
	{
		CLog::Log("No Character");
		return;
	}

	CLog::Log("Post Login In the Game");
	

	if (index >= Colors.Num())
		character->BodyColor = FLinearColor::Black;

	else
		character->BodyColor = Colors[index++];

	AllPC.Add(NewPlayer);
	UpdatePlayerList();
}

void APushGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	APlayerController* playercontroller = Cast<APlayerController>(Exiting);

	AllPC.Empty();
	UpdatePlayerList();
}

void APushGameMode::UpdatePlayerList()
{
	// 플레이어 리스트를 비워주고, Player의 이름을 가져와서 세팅
	PlayerListData.Empty();

	for (APlayerController* PlayerController : AllPC)
	{
		if (PlayerController)
		{
			APushPlayerController* pushController = Cast<APushPlayerController>(PlayerController);
			APawn* pawn = PlayerController->GetPawn();
			// 업데이트가 제대로 안되고 게임이 시작할 경우가 생겨서 0.2초뒤에 다시 함수 실행
			if (!pawn)
			{
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(
					TimerHandle, this, &APushGameMode::UpdatePlayerList, 0.2f, false);
			}

			else
			{
				// Lobby에서 입력된 이름인 CustomPlayerName이 출력되도록 변경
				APushCharacter* pushCharacter = Cast<APushCharacter>(pawn);
				if (pushCharacter)
				{
					UResourceComponent* resource = Helpers::GetComponent<UResourceComponent>(pushCharacter);

					PlayerData.PlayerName = pushCharacter->CustomPlayerName;
					PlayerData.Gold = resource->GetGold();
					PlayerData.Kill = resource->GetKill();
					PlayerData.Death = resource->GetDeath();

					PlayerListData.Add(PlayerData);
				}
			}
		}
	}

	// 플레이어 리스트 업데이트
	for (APlayerController* playerController : AllPC)
	{
		APushPlayerController* pushPlayerController = Cast<APushPlayerController>(playerController);

		if (pushPlayerController)
			pushPlayerController->UpdatePlayerList_Server(PlayerListData);
	}
}

void APushGameMode::PlayerDead(APushPlayerController* InController)
{
	if (MatchState == "TotalResult")
		return;

	PushGameState->AddToRank(InController);

	if (++NumofDeadPlayers >= (PushGameState->PlayerArray.Num() - 1))
	{
		if (Games >= TotalNumOfGames)
		{
			SetMatchState(MatchState::TotalResult);
			PushGameState->ShowTotalRank();
			SetActorTickEnabled(false);
			CurrentTime = 0.0f;
			return;
		}

		for (APlayerState* player : PushGameState->PlayerArray)
		{
			APushCharacter* character = Cast<APushCharacter>(player->GetPawn());

			if (character == nullptr)
				continue;

			UStateComponent* state = Helpers::GetComponent<UStateComponent>(character);

			if (state == nullptr)
				continue;

			if (!state->IsDeadMode())
			{
				APushPlayerController* controller = Cast<APushPlayerController>(character->GetController());

				if (controller == nullptr)
					continue;

				PushGameState->AddToRank(controller);
				break;
			}
		}
		tempTime = GetWorld()->GetTimeSeconds();
		CountdownTime = ResultTime;
		Round = 0;
		NumofDeadPlayers = 0;
		SetMatchState(MatchState::Result); // 결과발표
	}

}

void APushGameMode::RoundEnd()
{
	PushGameState->GiveGold(MoneyPerRank, BaseMoney);
	PushGameState->UpdateGameNum(++Games);
	PushGameState->Respawn();
	Ring->Reset();
}

void APushGameMode::RoundStart()
{
	PushGameState->RoundStart();
}

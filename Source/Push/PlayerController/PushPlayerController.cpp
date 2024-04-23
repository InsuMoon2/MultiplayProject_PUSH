#include "Push/PlayerController/PushPlayerController.h"
#include "HUD/MainHUD.h"
#include "GameMode/PushGameMode.h"
#include "Global.h"
#include "Character/PushCharacter.h"
#include "HUD/Resource.h"
#include "Net/UnrealNetwork.h"
#include "Components/ProgressBar.h"
#include "Components/ResourceComponent.h"
#include "Components/TextBlock.h"
#include "GameState/PushGameState.h"
#include "Widgets/KillDeathUI.h"
#include "Widgets/LeaderBoard_List.h"
#include "Widgets/MainUI.h"
#include "Widgets/StoreUI.h"
#include "Widgets/Rank.h"
#include "Components/MoveComponent.h"

void APushPlayerController::ShowRank_Client_Implementation(uint8 InRank, TSubclassOf<URank> InRankWidget)
{
	URank* RankWidget = CreateWidget<URank>(this, InRankWidget);

	FText text = FText::FromString(FString::FromInt(InRank));
	RankWidget->RankText->SetText(text);
	RankWidget->AddToViewport();
}

void APushPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MainHUD = Cast<AMainHUD>(GetHUD());

	if (IsValid(MainHUD))
	{
		MainHUD->AddWidget();
		//if (MainHUD->CheckWidget("LeaderBoard"))
		//	MainHUD->GetWidget<UKillDeathUI>("LeaderBoard")->SetVisibility(ESlateVisibility::Hidden);

		if (MainHUD->CheckWidget("LeaderBoard_List"))
			MainHUD->GetWidget<ULeaderBoard_List>("LeaderBoard_List")->SetVisibility(ESlateVisibility::Hidden);

		if (MainHUD->CheckWidget("Store"))
			MainHUD->GetWidget<UStoreUI>("Store")->SetVisibility(ESlateVisibility::Hidden);
	}

	PushGameMode = Cast<APushGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameState = Cast<APushGameState>(UGameplayStatics::GetGameState(this));
	pushCharacter = Cast<APushCharacter>(GetPawn());
}

void APushPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (GameState == nullptr) return;

	SetHUDTime(); // 시간
}

void APushPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TWeakObjectPtr<APushCharacter> PushCharacter = Cast<APushCharacter>(InPawn);
	resourceComponent = Helpers::GetComponent<UResourceComponent>(PushCharacter.Get());

}

void APushPlayerController::OnMatchStateSet(FName State)
{
	MatchState = State;  // GameMode에서 건내받는 FName State으로 MatchState 설정
}

void APushPlayerController::SetHUDTime() // 화면에 시간 띄우기
{
	if (MainHUD == nullptr) return;
	if (MainHUD->GetWidget<UResource>("Resource") == nullptr) return;
	
	TimeLeft = GameState->CurrentTime;
	MatchState = GameState->GetMatchState();

	UpdateCharacterMovement(MatchState);

	uint32 Countdown = FMath::CeilToInt(TimeLeft);

	// 시간 띄우기
	if (MainHUD->GetWidget<UResource>("Resource")->MatchCountdownText)
	{
		int32 Minutes = FMath::FloorToInt(Countdown / 60.f);
		int32 Seconds = Countdown - Minutes * 60;

		FString CountdownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
		MainHUD->GetWidget<UResource>("Resource")->MatchCountdownText->SetText(FText::FromString(CountdownText));
	}
	// MatchState 띄우기
	if (MainHUD->GetWidget<UResource>("Resource")->MatchStateTypeText)
	{
		FText name;
		if (MatchState == MatchState::InProgress) name = FText::FromString("Store");
		else if (MatchState == MatchState::Round) name = FText::FromString("Round");
		else if (MatchState == MatchState::Result) name = FText::FromString("Result");

		MainHUD->GetWidget<UResource>("Resource")->MatchStateTypeText->SetText(name);
	}

	// 결과발표가 끝나면 캐릭터 리스폰
	if (MatchState == MatchState::Result)
	{
		if (0.f < TimeLeft && TimeLeft < 0.18f)
		{
			pushCharacter->SetSpawnPoint();
		}		
	}
}

void APushPlayerController::UpdateCharacterMovement(const FName& matchState)
{
	if (PreMatchState != MatchState)
	{
		// 상점,결과시간 시 캐릭터 멈추고 스킬시전X, 라운드 시 캐릭터 움직임+스킬O
		if (matchState == MatchState::InProgress)
		{
			pushCharacter->MoveComponent->Stop();
			pushCharacter->bCanMove = false;
		}
		else if (matchState == MatchState::Round)
		{
			pushCharacter->MoveComponent->Move();
			pushCharacter->bCanMove = true;
		}
		else if (matchState == MatchState::Result)
		{
			pushCharacter->MoveComponent->Stop();
			pushCharacter->bCanMove = false;
		}
	}
	PreMatchState = MatchState;
}

void APushPlayerController::UpdateGameNum_Client_Implementation(uint8 InNumofGames)
{
	if (MainHUD == nullptr) return;
	if (MainHUD->CheckWidget("Resource") == false) return;

	FText text = FText::FromString(FString::FromInt(InNumofGames));
	MainHUD->GetWidget<UResource>("Resource")->GameText->SetText(text);
}

void APushPlayerController::UpdatePlayerList_Server_Implementation(const TArray<FPlayerList>& PlayerList)
{
	UpdatePlayerList_NMC(PlayerList);
}

void APushPlayerController::UpdatePlayerList_NMC_Implementation(const TArray<FPlayerList>& PlayerList)
{
	if (MainHUD == nullptr) return;
	if (MainHUD->GetWidget<UKillDeathUI>("LeaderBoard") == nullptr) return;

	// 정상적으로 호출이 되었으면, PlayerList Update
	MainHUD->GetWidget<UKillDeathUI>("LeaderBoard")->UpdatePlayerList(PlayerList);
}

void APushPlayerController::ShowKillLog_Server_Implementation(const FString& InKillPlayer, const FString& InDeadPlayer)
{
	ShowKillLog_NMC(InKillPlayer, InDeadPlayer);
}

void APushPlayerController::ShowKillLog_NMC_Implementation(const FString& InKillPlayer, const FString& InDeadPlayer)
{
	if (MainHUD == nullptr) return;

	if (MainHUD->CheckWidget("Main"))
	{
		MainHUD->GetWidget<UMainUI>("Main")->Add_KillFeed(InKillPlayer, InDeadPlayer);
	}
}
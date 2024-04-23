#include "Push/GameState/PushGameState.h"
#include "Character/PushCharacter.h"
#include "Components/ResourceComponent.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "PlayerController/PushPlayerController.h"
#include "Utilites/Helpers.h"
#include "Widgets/Rank.h"
#include "Components/TextBlock.h"
#include "Utilites/CLog.h"
#include "Objects/PlayerBox.h"
#include "GameFramework/PlayerStart.h"

APushGameState::APushGameState()
{
	CurrentTime = 0.0f;
}

void APushGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APushGameState, CurrentTime);
	DOREPLIFETIME(APushGameState, RoundRank);
}

void APushGameState::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> tempbox, tempstart;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerBox::StaticClass(), tempbox);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), tempstart);

	for(AActor* tmp : tempbox)
	{
		APlayerBox* box = Cast<APlayerBox>(tmp);

		if (box == nullptr)
			continue;

		Boxes.Push(box);
	}

	for (AActor* tmp : tempstart)
	{
		APlayerStart* start = Cast<APlayerStart>(tmp);

		if (start == nullptr)
			continue;

		Starts.Push(start);
	}
}

void APushGameState::SetTime(float InTime)
{
	CurrentTime = InTime;
}

void APushGameState::UpdateGameNum(uint8 InNumofGames)
{
	for (APlayerState* player : PlayerArray)
	{
		APushCharacter* character = Cast<APushCharacter>(player->GetPawn());

		if (character == nullptr)
			continue;

		APushPlayerController* controller = Cast<APushPlayerController>(character->GetController());

		if (controller == nullptr)
			continue;

		controller->UpdateGameNum_Client(InNumofGames);
	}
}

void APushGameState::ShowTotalRank()
{
	TArray<APushPlayerController*> Controllers;


	for (APlayerState* player : PlayerArray)
	{
		APushCharacter* character = Cast<APushCharacter>(player->GetPawn());

		if (character == nullptr)
			continue;

		APushPlayerController* controller = Cast<APushPlayerController>(character->GetController());

		if (controller == nullptr)
			continue;

		Controllers.Add(controller);
	}

	Controllers.Sort([](APushPlayerController& A, APushPlayerController& B)
	{
		uint8 AKill = A.resourceComponent->GetKill();
		uint8 BKill = B.resourceComponent->GetKill();

		return AKill > BKill;
	});

	int Rank = 1;
	uint8 CurrentKill = Controllers[0]->resourceComponent->GetKill();

	if (Controllers.Num() == 0)
		CLog::Log("Controllers Empty");

	for (APushPlayerController* controller : Controllers)
	{
		uint8 thisKill = controller->resourceComponent->GetKill();

		CLog::Log(thisKill);
		if (thisKill < CurrentKill)
		{
			Rank++;
			CurrentKill = thisKill;
		}

		controller->ShowRank_Client(Rank, RankWidget);
	}
}

void APushGameState::RoundEnd_NMC_Implementation()
{
	if (OnRoundEnd.IsBound() == true)
		OnRoundEnd.Broadcast();
}

void APushGameState::GiveGold(TArray<int32> InGoldAmount, int32 InBaseMoney)
{
	CLog::Log("GiveGold");
	int num = RoundRank.Num();
	for (uint8 i = 0; i < num; i++)
	{
		APushPlayerController* controller = RoundRank.Pop();
		UResourceComponent* resource = Helpers::GetComponent<UResourceComponent>(controller->GetCharacter());

		CLog::Log(InGoldAmount[i]);
		resource->AdjustGold_NMC(InGoldAmount[i] + InBaseMoney);
	}
}

void APushGameState::Respawn()
{
	for (APlayerBox* box : Boxes)
	{
		box->ToggleCollision_NMC(true);
	}

	for(int i = 0; i < PlayerArray.Num(); i++)
	{
		APushCharacter* character = Cast<APushCharacter>(PlayerArray[i]->GetPawn());

		if (character == nullptr)
			continue;

		character->SetSpawnPointNMC(Starts[i % Starts.Num()]->GetActorLocation());
	}

	RoundEnd_NMC();
}

void APushGameState::RoundStart()
{
	for(APlayerBox* box : Boxes)
	{
		box->ToggleCollision_NMC(false);
	}
}

void APushGameState::AddToRank(APushPlayerController* InController)
{

	RoundRank.AddUnique(InController);
}

#include "Components/ResourceComponent.h"
#include "PlayerController/PushPlayerController.h"
#include "Character/PushCharacter.h"
#include "HUD/MainHUD.h"
#include "Widgets/KillDeathUI.h"
#include "Net/UnrealNetwork.h"
#include "Global.h"
#include "GameMode/PushGameMode.h"
#include "HUD/Resource.h"
#include "Components/TextBlock.h"

UResourceComponent::UResourceComponent()
{

}

void UResourceComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<APushCharacter>(GetOwner());
	if (Owner.IsValid() == false) return;

	PushGameMode = Cast<APushGameMode>(UGameplayStatics::GetGameMode(Owner->GetWorld()));
}

void UResourceComponent::PlusDeathCount()
{
	Death++;
}

void UResourceComponent::PlusKillCount()
{
	Kill++;
}

void UResourceComponent::SetHP_Server_Implementation(float hp)
{
	SetHP_NMC(hp);
}

void UResourceComponent::SetHP_NMC_Implementation(float hp)
{
	HP = hp;
}

void UResourceComponent::SetMaxHP_Server_Implementation(float maxHP)
{
	SetMaxHP_NMC(maxHP);
}

void UResourceComponent::SetMaxHP_NMC_Implementation(float maxHP)
{
	MaxHP = maxHP;
}

// 2024.01.02 이현중
// 현재 수치에 Value값을 현재HP에 plus 최대값은 0~MaxHP까지

void UResourceComponent::AdjustHP_Server_Implementation(int InValue)
{
	AdjustHP_NMC(InValue);
}

void UResourceComponent::AdjustHP_NMC_Implementation(int InValue)
{
	HP = FMath::Clamp(HP + InValue, 0.0f, MaxHP);
}

void UResourceComponent::AdjustHP(int InValue)
{
	HP = FMath::Clamp(HP + InValue, 0.0f, MaxHP);
}

void UResourceComponent::OnKillDeathUI()
{
	TWeakObjectPtr<APushPlayerController> playerController = Cast<APushPlayerController>(Owner->GetController());
	if (false == playerController.IsValid()) return;

	MainHUD = MainHUD == nullptr ? Cast<AMainHUD>(playerController->GetHUD()) : MainHUD;

	if (false == IsValid(MainHUD)) return;

	if (MainHUD->CheckWidget("LeaderBoard"))
	{
		MainHUD->GetWidget<UKillDeathUI>("LeaderBoard")->OpenLeaderBoard();
	}
}

void UResourceComponent::OffKillDeathUI()
{
	TWeakObjectPtr<APushPlayerController> playerController = Cast<APushPlayerController>(Owner->GetController());

	if (false == playerController.IsValid()) return;

	MainHUD = MainHUD == nullptr ? Cast<AMainHUD>(playerController->GetHUD()) : MainHUD;

	if (false == IsValid(MainHUD)) return;

	if (MainHUD->CheckWidget("LeaderBoard"))
	{
		MainHUD->GetWidget<UKillDeathUI>("LeaderBoard")->OffLeaderBoard();
	}
}

void UResourceComponent::SetGold_Server_Implementation(int InValue)
{
	SetGold_NMC(InValue);
}

void UResourceComponent::SetGold_NMC_Implementation(int InValue)
{
	Gold = InValue;
}

int UResourceComponent::GetGold()
{
	return Gold;
}

void UResourceComponent::AdjustGold_Server_Implementation(int InValue)
{
	AdjustGold_NMC(InValue);
}


void UResourceComponent::AdjustGold_NMC_Implementation(int InValue)
{
	// 골드제한 할거면 Clamp 추가
	Gold += InValue;

	// 위젯 업데이트
	if (PushGameMode)
		PushGameMode->UpdatePlayerList();

	TWeakObjectPtr<APushPlayerController> playerController = Cast<APushPlayerController>(Owner->GetController());

	if (false == playerController.IsValid()) return;

	MainHUD = MainHUD == nullptr ? Cast<AMainHUD>(playerController->GetHUD()) : MainHUD;

	if (false == IsValid(MainHUD)) return;

	if(MainHUD->CheckWidget("Resource"))
	{
		FText gold = FText::FromString(FString::FromInt(Gold));
		MainHUD->GetWidget<UResource>("Resource")->GoldText->SetText(gold);
	}

}

int UResourceComponent::GetKill()
{
	return Kill;
}

void UResourceComponent::AdjustKill_Server_Implementation(int32 InValue)
{
	AdjustKill_NMC(InValue);
	CLog::Log("ADJKILL_SERVER");
}

void UResourceComponent::AdjustKill_NMC_Implementation(int32 InValue)
{
	if (InValue <= 0) return;

	//Kill += InValue;

	CLog::Log("ADJKILL_NMC");

	if (PushGameMode)
		PushGameMode->UpdatePlayerList();

	TWeakObjectPtr<APushPlayerController> playerController = Cast<APushPlayerController>(Owner->GetController());

	if (false == playerController.IsValid()) return;

	MainHUD = MainHUD == nullptr ? Cast<AMainHUD>(playerController->GetHUD()) : MainHUD;

	if (false == IsValid(MainHUD)) return;

	if (MainHUD->CheckWidget("Resource"))
	{
		FText kill = FText::FromString(FString::FromInt(Kill));
		MainHUD->GetWidget<UResource>("Resource")->KillText->SetText(kill);
	}
}

int UResourceComponent::GetDeath()
{
	return Death;
}

void UResourceComponent::AdjustDeath_Server_Implementation(int32 InValue)
{
	AdjustDeath_NMC(InValue);
}

void UResourceComponent::AdjustDeath_NMC_Implementation(int32 InValue)
{
	if (InValue <= 0) return;

	Death += InValue;

	if (PushGameMode)
		PushGameMode->UpdatePlayerList();

	TWeakObjectPtr<APushPlayerController> playerController = Cast<APushPlayerController>(Owner->GetController());

	if (false == playerController.IsValid()) return;

	MainHUD = MainHUD == nullptr ? Cast<AMainHUD>(playerController->GetHUD()) : MainHUD;

	if (false == IsValid(MainHUD)) return;

	if (MainHUD->CheckWidget("Resource"))
	{
		FText death = FText::FromString(FString::FromInt(Death));
		MainHUD->GetWidget<UResource>("Resource")->DeathText->SetText(death);
	}

}

void UResourceComponent::ShowKillLog(AActor* InAttacker, APushCharacter* InHitted)
{
	FString killerName;
	FString deadName = InHitted->CustomPlayerName;

	APushCharacter* killPlayer = Cast<APushCharacter>(InAttacker);

	if(killPlayer == nullptr)
	{
		killerName = FString("ring");
	}
	else
	{
		killerName = killPlayer->CustomPlayerName;
	}
	
	TArray<AActor*> PlayerControllers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APushPlayerController::StaticClass(), PlayerControllers);

	for (AActor* Actor : PlayerControllers)
	{
		APushPlayerController* PlayerController = Cast<APushPlayerController>(Actor);
		if (PlayerController)
		{
			if(Owner->HasAuthority())
				PlayerController->ShowKillLog_Server(killerName, deadName);
		}
	}
}



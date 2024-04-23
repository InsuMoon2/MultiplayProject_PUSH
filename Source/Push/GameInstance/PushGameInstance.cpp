#include "GameInstance/PushGameInstance.h"
#include "Online.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"

FString UPushGameInstance::GetPlayerName()
{
	return PlayerName;
}

void UPushGameInstance::SetPlayerName(const FString& InPlayerName)
{
	PlayerName = InPlayerName;
}

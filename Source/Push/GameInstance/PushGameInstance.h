#pragma once
#include "CoreMinimal.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PushGameInstance.generated.h"

UCLASS(Blueprintable)
class PUSH_API UPushGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FString GetPlayerName();

	UFUNCTION(BlueprintCallable)
		void SetPlayerName(const FString& InPlayerName);

private:
	FString PlayerName;

};

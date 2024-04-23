#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Misc/Structures.h"
#include "LobbyReadyState.generated.h"

UCLASS()
class PUSH_API ULobbyReadyState : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void UpdatePlayerData(const FLobbyData& InLobbyData);

};

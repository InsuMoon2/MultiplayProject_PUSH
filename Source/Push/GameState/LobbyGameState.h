#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "LobbyGameState.generated.h"

UCLASS()
class PUSH_API ALobbyGameState : public AGameState
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void PlayerConnection(int InPlayerNum);

	UFUNCTION()
		void CountDown(int InCountdown);

	FTimerHandle LobbyTimeHandle;

public:
	UPROPERTY(Replicated)
		int NumofPlayers = 0;

	UPROPERTY(Replicated)
		int Count = 0;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
};

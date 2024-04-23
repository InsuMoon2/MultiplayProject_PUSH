#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Misc/Structures.h"
#include "LobbyGameMode.generated.h"

/** 게임 시작 시 GameMode
 *
 */

UCLASS()
class PUSH_API ALobbyGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	UFUNCTION(Server, Reliable)
		void PlayerLoginInServer();

	UPROPERTY(EditAnywhere)
		uint8 MaxNumofPlayers = 3;

	UPROPERTY(EditAnywhere)
		uint8 StartCountdown = 5;

	void Tick(float DeltaSeconds) override;

	void CountDown();
	void EnterMap();

public:
	UFUNCTION(BlueprintCallable)
		void UpdateLobbyInfo(APlayerController* InPlayerController);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void OnCheckPlayerAllReady();

public:
	UPROPERTY(BlueprintReadWrite)
		TArray<class APlayerController*> AllPC;

	UPROPERTY(EditAnywhere, Category = "LobbyData")
		TArray<FLobbyData> LobbyDatas;

	UPROPERTY(BlueprintReadWrite)
		TArray<class ALobbyPlayerPlatform*> LobbyPlatforms;

	FLobbyData LobbyData;

private:
	uint8 NumOfPlayers = 0;
	int countdownTimer = 0;
	FTimerHandle LobbyTimeHandle;

	bool bAllPlayerReady = false;

};

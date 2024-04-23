#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Misc/Structures.h"
#include "LobbyPlayerController.generated.h"

UCLASS()
class PUSH_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnPossess(APawn* InPawn) override;

public:
	UFUNCTION(Client, Unreliable)
		void UpdatePlayerNum_Client(int InNum);

	UFUNCTION(Client, Unreliable)
		void UpdateTimer_Client(int InTime);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void TryAgainUpdatingLobbyInfo();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void SetUpLobbyInfo();

	UFUNCTION(Server, Reliable)
		void SetPlayerName_Server(const FString& InPlayerName);

	UFUNCTION(Server, Reliable)
		void OnReadyButton_Clicked_Server();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnReadyButton_Clicked();

	UPROPERTY(BlueprintReadWrite)
		class ALobbyGameMode* LobbyGameMode;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ULobbyReadyButton> ReadyButton;

	class ULobbyReadyButton* LobbyReadyButton;

	FLobbyData PlayerLobbyData;

	class ALobbyHUD* LobbyHUD;

};

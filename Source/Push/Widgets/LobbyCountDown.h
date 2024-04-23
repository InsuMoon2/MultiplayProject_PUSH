#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyCountDown.generated.h"

/** Lobby에서 사용되는 위젯
 *
 */
UCLASS(Blueprintable)
class PUSH_API ULobbyCountDown : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* PlayerAmount; // 입장한 플레이어 수
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* CountDown; // 카운트 다운

	UFUNCTION()
		void UpdateWidget();

	UFUNCTION()
		void SetPlayerNum(int InNum);

	UFUNCTION()
		void SetCountdown(int InNum);

private:
	int NumofPlayers = 0;
	int Countdown = 0;
};
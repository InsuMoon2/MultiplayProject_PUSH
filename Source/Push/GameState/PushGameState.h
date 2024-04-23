#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PushGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoundEnd_GS);

UCLASS()
class PUSH_API APushGameState : public AGameState
{
	GENERATED_BODY()

public:
	APushGameState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void BeginPlay() override;

	UPROPERTY(Replicated)
		float CurrentTime;

	UFUNCTION()
		void SetTime(float InTime);

public:
	UFUNCTION(BlueprintCallable)
		void AddToRank(class APushPlayerController* InController);

	UFUNCTION()
		void UpdateGameNum(uint8 InNumofGames);

	UFUNCTION()
		void ShowTotalRank();

	UFUNCTION(NetMulticast, Reliable)
		void RoundEnd_NMC();

	void GiveGold(TArray<int32> InGoldAmount, int32 InBaseMoney);
	void Respawn();
	void RoundStart();

	UPROPERTY(VisibleAnywhere, Replicated)
		TArray<class APushPlayerController*> RoundRank;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class URank> RankWidget;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FOnRoundEnd_GS OnRoundEnd;

private:
	TArray<class APlayerBox*> Boxes;
	TArray<class APlayerStart*> Starts;
};
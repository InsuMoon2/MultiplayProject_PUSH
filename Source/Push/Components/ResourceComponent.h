#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResourceComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PUSH_API UResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UResourceComponent();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE float GetHP() { return HP; }
	FORCEINLINE float GetMaxHP() { return MaxHP; }

	void PlusDeathCount();
	void PlusKillCount();

	//2024.01.09 이현중
	//기존 INLINE함수 RPC를 이용한 함수로 변경
	UFUNCTION(Server, Reliable)
		void SetHP_Server(float hp);

	UFUNCTION(Server, Reliable)
		void SetMaxHP_Server(float maxHP);

	UFUNCTION(Server, Reliable)
		void AdjustHP_Server(int InValue);

	UFUNCTION(NetMulticast, Reliable)
		void SetHP_NMC(float hp);

	UFUNCTION(NetMulticast, Reliable)
		void SetMaxHP_NMC(float maxHP);

	UFUNCTION(NetMulticast, Reliable)
		void AdjustHP_NMC(int InValue);

	void AdjustHP(int InValue);

	// 2024_01_04 박성우 - Tab키 입력 시 KillDeath 위젯 띄우기
	void OnKillDeathUI();
	void OffKillDeathUI();

	// 2024_01_15 문인수 - Gold
	UFUNCTION(Server, Reliable, BlueprintCallable)
		void SetGold_Server(int InValue);

	UFUNCTION(NetMulticast, Reliable)
		void SetGold_NMC(int InValue);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		int32 GetGold();

	UFUNCTION(Server, Reliable, BlueprintCallable)
		void AdjustGold_Server(int32 InValue);

	UFUNCTION(NetMulticast, Reliable)
		void AdjustGold_NMC(int32 InValue);

	// Kill, Death
	UFUNCTION(BlueprintCallable, BlueprintPure)
		int32 GetKill();

	UFUNCTION(Server, Reliable, BlueprintCallable)
		void AdjustKill_Server(int32 InValue);

	UFUNCTION(NetMulticast, Reliable)
		void AdjustKill_NMC(int32 InValue);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		int32 GetDeath();

	UFUNCTION(Server, Reliable, BlueprintCallable)
		void AdjustDeath_Server(int32 InValue);

	UFUNCTION(NetMulticast, Reliable)
		void AdjustDeath_NMC(int32 InValue);

	void ShowKillLog(AActor* InAttacker, class APushCharacter* InHitted);

private:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Property",
		meta = (AllowPrivateAccess))
		float HP = 100.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Property",
	meta = (AllowPrivateAccess))
		float MaxHP = 100.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Property",
		meta = (AllowPrivateAccess))
		int32 Gold = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Property",
		meta = (AllowPrivateAccess))
		int32 Kill = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Property",
		meta = (AllowPrivateAccess))
		int32 Death = 0;

	class APushGameMode* PushGameMode;

	UPROPERTY()
	class AMainHUD* MainHUD;

	TWeakObjectPtr<class APushCharacter> Owner;

};

// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/Damageable.h"
#include "PushCharacter.generated.h"

UCLASS(config = Game)
class APushCharacter : public ACharacter, public IDamageable
{
	GENERATED_BODY()

public:
	APushCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	UPROPERTY(VisibleInstanceOnly)
		class UWDG_EffectBase* widget;

	//2024_01_02 서동주 Hit Interface 적용
	virtual void Hit(AActor* InAttacker, const FHitData& InHitData) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UResourceComponent* ResourceComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UMoveComponent* MoveComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class USkillComponent* SkillComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UBuffComponent* BuffComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UItemComponent* ItemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UShopComponent* ShopComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UStateComponent* StateComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere, Category = "CameraShakeBase")
		TSubclassOf<UCameraShakeBase> CameraShakeBase;

	UPROPERTY(EditAnywhere, Category = "Dead Montage")
		class UAnimMontage* DeadMontage;

	/*UPROPERTY(BlueprintReadWrite)
		class USkillSlots* SkillSlots;*/

	/*UPROPERTY(BlueprintReadWrite)
		class USkillSlots* ItemSlots;*/

	UPROPERTY(BlueprintReadOnly)
		bool bCanMove;

public:
	UFUNCTION(Server, Reliable)
		void LaunchServer(FVector InLaunch);

	UFUNCTION(NetMulticast, Reliable)
		void LaunchNMC(FVector InLaunch);

	// 2024_01_23 캐릭터 위치 변경 _이민학
	UFUNCTION(Server, Reliable)
		void SetLocation(FVector InLocation);

	void DoCameraShake(float Damage);

	// 2024_01_05 Material Change 적용
	void Create_DynamicMaterial();
	void Change_Color(FLinearColor InColor);

	//Testing!!
	UFUNCTION(BlueprintCallable)
		void Test();

public:
	UPROPERTY(Replicated)
		FLinearColor BodyColor;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	// 24_01_17 문인수
	UPROPERTY(Replicated, BlueprintReadWrite)
		FString CustomPlayerName;

	void SetUpLocalName();

	UFUNCTION(Server, Reliable)
		void SetPlayerNameServer(const FString& NewPlayerName);

	void UpdatePlayerLobbyInfo(const FLobbyData& InLobbyInfo);

	UFUNCTION()
		void OnRep_PlayerLobbyInfo();

	UPROPERTY(ReplicatedUsing="OnRep_PlayerLobbyInfo")
		FLobbyData PlayerLobbyInfo;

	void Ragdoll();
	void CharacterDead();

	UFUNCTION(Server, Reliable)
		void SetSpawnPoint();
	UFUNCTION(NetMulticast, Reliable)
		void SetSpawnPointNMC(FVector InLocation);

	UFUNCTION(BlueprintCallable, Server, Reliable)
		void Dead_Server();

private:
	UPROPERTY(Replicated)
		APushCharacter* Attacker;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ReadyMontage", meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*> Ready_Montage;

	UFUNCTION(Server, Reliable)
		void SetAttacker_Server(APushCharacter* InAttacker);

	UFUNCTION(NetMulticast, Reliable)
		void SetAttacker_NMC(APushCharacter* InAttacker);

};


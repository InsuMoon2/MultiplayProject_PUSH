#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ring.generated.h"

UCLASS()
class PUSH_API ARing : public AActor
{
	GENERATED_BODY()
	
public:	
	ARing();

public:
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
public:	
	virtual void Tick(float DeltaTime) override;

public:
	//Collision을 담당하는 Capsule
	UPROPERTY(EditAnywhere, Replicated)
		class UCapsuleComponent* RingCapsule;

	//자기장 생김새를 담당하는 Mesh
	UPROPERTY(EditAnywhere, Replicated)
		class UStaticMeshComponent* RingMesh;

	//자기장 피해량
	UPROPERTY(EditAnywhere)
		float RingDamage = 1.0f;

	//자기장 이펙트 Widget
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UWDG_EffectBase> DamageEffectWidget;

public:
	//2024_01_02 서동주 자기장 크기 줄이는 함수
	//InRadius: 줄어들 자기장 반지름 크기, InTime: 줄어들 시간 (초단위)
	UFUNCTION(BlueprintCallable)
		void Shrink(float InRadius, float InTime);

	//Timer를 통해 자기장 줄어드는 것을 적용하는 함수
	UFUNCTION(BlueprintCallable)
		void ChangeRadius();

	//OnConstruction 때 Mesh와 Capsule의 크기를 맞춰주기 위한 함수
	UFUNCTION()
		void Refresh();

	UFUNCTION()
		void Reset();

	UFUNCTION(NetMulticast, Reliable)
		void SetCapsuleRadius_NMC(float InRadius);

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	// Base로 나누어 비율 계산하면 Capsule과 Mesh의 크기가 딱 맞습니다
	float Base = 50.0f;

	TArray<class APushCharacter*> OverlappedCharacters;
	FTimerHandle TimerHandle;

	float DeltaRadius = 0.0f;
	float TargetRadius;
	float StartRadius;
};

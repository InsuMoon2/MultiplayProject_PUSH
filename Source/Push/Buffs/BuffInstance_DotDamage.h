#pragma once

#include "CoreMinimal.h"
#include "Buffs/BuffInstance.h"
#include "BuffInstance_DotDamage.generated.h"

UCLASS()
class PUSH_API ABuffInstance_DotDamage : public ABuffInstance
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

	//2024.01.09
	//효과를 설정하는 함수
	virtual void Active();

public:
	UPROPERTY(EditAnywhere)
		float DotDelay = 1.0f;

	UPROPERTY(EditAnywhere)
		float Damage = 1.0f;

	float DotPlayTime = 0.0f;
};

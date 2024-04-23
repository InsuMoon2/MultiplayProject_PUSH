#pragma once

#include "CoreMinimal.h"
#include "Buffs/BuffInstance.h"
#include "BuffInstance_Healing.generated.h"

UCLASS()
class PUSH_API ABuffInstance_Healing : public ABuffInstance
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void Active();

public:
	UPROPERTY(EditAnywhere)
		float HealDelay = 2.0f;

	UPROPERTY(EditAnywhere)
		float Restoration = 5.0f;

	float healPlayTime = 0.0f;
};

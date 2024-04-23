#pragma once

#include "CoreMinimal.h"
#include "Buffs/BuffInstance.h"
#include "BuffInstance_FastMove.generated.h"

UCLASS(Blueprintable)
class PUSH_API ABuffInstance_FastMove : public ABuffInstance
{
	GENERATED_BODY()

public:
	virtual void OnEffect() override;
	virtual void OffEffect() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, Category = "Property",
		meta = (ClampMin = "0", ClampMax = "100.0", UIMin = "0", UIMax = "100.0"))
		float PlusSpeedPercent = 20.0f;

	class UCharacterMovementComponent* movementComponent;
};

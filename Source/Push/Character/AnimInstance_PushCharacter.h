#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstance_PushCharacter.generated.h"

UCLASS()
class PUSH_API UAnimInstance_PushCharacter : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		float Pitch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		bool Falling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		bool bUseControlYaw;
public:
	//2024.01.16 이현중
	//빙결상태를 위한 Snapshot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		bool IsSnapshot = false;

public:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	class APushCharacter* OwnerCharacter;
	class UMoveComponent* Movement;

	FRotator PrevRotation;

};

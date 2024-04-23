#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Misc/Enums.h"
#include "NF_BeginAction.generated.h"

UCLASS()
class PUSH_API UNF_BeginAction : public UAnimNotify
{
	GENERATED_BODY()

public:
	FString GetNotifyName_Implementation() const override;
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	UPROPERTY(EditAnywhere)
		EStateType StateType;

	UPROPERTY(EditAnywhere)
		bool bMoveCheck = false;
};

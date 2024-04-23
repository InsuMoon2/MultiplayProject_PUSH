#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Misc/Structures.h"
#include "SkillData.generated.h"

UCLASS(Blueprintable, BlueprintType)
class PUSH_API USkillData : public UObject
{
	GENERATED_BODY()

public:
	virtual void BeginPlay();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FProduct Product;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ASkill> Skill;

	UPROPERTY(EditAnywhere)
		float RelativeDistance = 0;

	UPROPERTY(EditAnywhere)
		FVector RelativeLocation = FVector::ZeroVector;

public:
	UFUNCTION()
	virtual void Play(ACharacter* InOwner);

	virtual void Destroy_TracePoint(){};
};
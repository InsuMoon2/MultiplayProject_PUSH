#pragma once

#include "CoreMinimal.h"
#include "Skill/Skill.h"
#include "Skill_Spawner.generated.h"

UCLASS()
class PUSH_API ASkill_Spawner : public ASkill
{
	GENERATED_BODY()

public:
	ASkill_Spawner();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* SpawnBox;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ASkill> SpawnedSkill;

	UPROPERTY(EditAnywhere)
		int LoopCount;
};

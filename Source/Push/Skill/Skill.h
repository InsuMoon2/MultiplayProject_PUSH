#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Misc/Structures.h"
#include "Skill.generated.h"

UCLASS(Abstract)
class PUSH_API ASkill : public AActor
{
	GENERATED_BODY()
	
public:	
	ASkill();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual void OnSkillPressed() {}
	virtual void OnSkillClicked() {}

protected:
	class ACharacter* Owner;

public:
	UPROPERTY(EditAnywhere, Category = "HitData")
		FHitData HitData;


};

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillData.h"
#include "SkillData_Projectile.generated.h"

UCLASS(Blueprintable, BlueprintType)
class PUSH_API USkillData_Projectile : public USkillData
{
	GENERATED_BODY()


public:
	virtual void Play(ACharacter* InOwner) override;
};

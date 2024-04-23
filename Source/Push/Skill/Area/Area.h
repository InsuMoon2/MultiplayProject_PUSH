#pragma once

#include "CoreMinimal.h"
#include "Skill/Skill.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Area.generated.h"

UCLASS(Abstract)
class PUSH_API AArea : public ASkill
{
	GENERATED_BODY()

public:
	AArea();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

public:
	virtual void OnSkillPressed() override;
	virtual void OnSkillClicked() override;

	virtual void OnSpawnPointDecal(FVector InLocation) {};
	virtual void OnDestroy(FVector InLocation) {};


protected:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

	UPROPERTY(EditAnywhere, Category = "DebugType")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebug;

	UPROPERTY(BlueprintReadWrite)
		FVector DecalLocation;
};
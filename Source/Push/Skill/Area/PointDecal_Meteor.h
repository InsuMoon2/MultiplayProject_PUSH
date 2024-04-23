#pragma once

#include "CoreMinimal.h"
#include "Skill/Area/PointDecal.h"
#include "PointDecal_Meteor.generated.h"

UCLASS()
class PUSH_API APointDecal_Meteor : public APointDecal
{
	GENERATED_BODY()

public:
	APointDecal_Meteor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void SetDecalTime(float InDecalTime) override;

private:
	float DecalTime;

	float Radius = 0.0f;
	float MaxRadius = 0.5f;
	float InterpSpeed = 0.0f;

	float CurrentTime;
};

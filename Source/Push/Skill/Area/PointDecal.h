#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "PointDecal.generated.h"

UCLASS(Blueprintable)
class PUSH_API APointDecal : public AActor
{
	GENERATED_BODY()
	
public:	
	APointDecal();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual void SetDecalTime(float InDecalTime) {};

private:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

protected:
	UPROPERTY(EditAnywhere, Category = "Decal")
		class UDecalComponent* PointDecal;

	class UMaterialInstanceDynamic* Dynamic;

};

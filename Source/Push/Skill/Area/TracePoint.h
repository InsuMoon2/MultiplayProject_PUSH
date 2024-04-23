#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TracePoint.generated.h"

UCLASS(Blueprintable)
class PUSH_API ATracePoint : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

	UPROPERTY(EditAnywhere, Category = "Decal")
		class UDecalComponent* TracePoint;

	UPROPERTY(EditAnywhere, Category = "Debug")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebug_Decal;

	// TraceTypeQuery1 = Camera
	UPROPERTY(EditAnywhere, Category = "Debug")
		TEnumAsByte<ETraceTypeQuery> TraceType = TraceTypeQuery1;

	UPROPERTY(EditAnywhere, Category = "Debug")
		float MaxDistance = 2000.0f;
	
public:	
	ATracePoint();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintPure)
		FVector GetTraceLocation() { return TraceLocation;  }

	void TraceDecal();

private:
	ACharacter* Owner;

	FVector TraceLocation;
	bool bShowDecal = false;

};

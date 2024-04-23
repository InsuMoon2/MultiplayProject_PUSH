#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerBox.generated.h"

UCLASS()
class PUSH_API APlayerBox : public AActor
{
	GENERATED_BODY()
	
public:	
	APlayerBox();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		USceneComponent* Root;

	UFUNCTION(NetMulticast, Reliable)
		void ToggleCollision_NMC(bool InBool);

private:
	TArray<class UBoxComponent*> Boxes;
};

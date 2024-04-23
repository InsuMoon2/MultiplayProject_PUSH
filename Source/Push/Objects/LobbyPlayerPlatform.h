#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LobbyPlayerPlatform.generated.h"

UCLASS(Blueprintable)
class PUSH_API ALobbyPlayerPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	ALobbyPlayerPlatform();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void SpawnCharacter(APlayerController* InPlayerController);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void Clear();

private:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Cube;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* PlayerSpawnTransform;

public:
	UPROPERTY(BlueprintReadWrite)
		class APlayerController* PlayerController;

	UPROPERTY(BlueprintReadWrite)
		AActor* CurrentCharacter;
};

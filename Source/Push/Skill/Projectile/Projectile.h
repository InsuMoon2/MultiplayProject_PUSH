#pragma once

#include "CoreMinimal.h"
#include "Skill/Skill.h"
#include "Misc/Structures.h"
#include "Projectile.generated.h"

UCLASS()
class PUSH_API AProjectile : public ASkill
{
	GENERATED_BODY()

public:
	AProjectile();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void OnDestroy();

public:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UParticleSystemComponent* Particle;

	UPROPERTY(EditAnywhere)
		class USphereComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UProjectileMovementComponent* ProjectileComponent;

public:
	UPROPERTY(EditAnywhere, Category = "Init")
		FProjectileData Datas;

public:
	UFUNCTION()
		virtual void FOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	FRotator rotation;
	FVector velocity;

};

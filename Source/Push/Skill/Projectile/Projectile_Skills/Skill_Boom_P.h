#pragma once

#include "CoreMinimal.h"
#include "Skill/Projectile/Projectile.h"
#include "Skill_Boom_P.generated.h"

UCLASS()
class PUSH_API ASkill_Boom_P : public AProjectile
{
	GENERATED_BODY()

public:
	ASkill_Boom_P();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Destroyed() override;

public:
	UPROPERTY(EditAnywhere, Category = "Spawn Particle")
		class UParticleSystem* SpawnParticle;

	UPROPERTY(EditAnywhere, Category = "Explosion Particle")
		class UParticleSystem* Explosion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USphereComponent* DetectTarget;

	UPROPERTY(EditAnywhere)
		float Speed = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class APushCharacter* Target;

public:
	virtual void FOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};

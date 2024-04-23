#pragma once

#include "CoreMinimal.h"
#include "Skill/Projectile/Projectile.h"
#include "Skill_Transball_P.generated.h"

UCLASS()
class PUSH_API ASkill_Transball_P : public AProjectile
{
	GENERATED_BODY()

public:
	ASkill_Transball_P();
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "Trans Particle")
		class UParticleSystem* TransParticle;

public:
	virtual void FOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};

#pragma once

#include "CoreMinimal.h"
#include "Skill/Area/Area.h"
#include "Interface/Damageable.h"
#include "Skill_Mine_A.generated.h"

UCLASS()
class PUSH_API ASkill_Mine_A : public AArea, public IDamageable
{
	GENERATED_BODY()

public:
	ASkill_Mine_A();
	virtual void BeginPlay() override;
	virtual void Hit(AActor* InAttacker, const FHitData& InHitData) override;

	UFUNCTION()
		void OnActivateOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnExplosionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnFinishParticle(class UParticleSystemComponent* PSystem);

	void ActiveExplosion();
protected:

	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* ActivationCollision;

	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* ExplosionCollision;

	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* ExplosionParticleComponent;
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* BaseParticleComponent;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* ExplosionParticle;
	UPROPERTY(EditAnywhere)
		class UParticleSystem* BaseParticle;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABuffInstance> BuffClass;

	TArray<AActor*> hitted;

	UPROPERTY(EditAnywhere)
		float DelayTime = 2.0f;
};



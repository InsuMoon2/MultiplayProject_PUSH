#pragma once

#include "CoreMinimal.h"
#include "Skill/Area/Area.h"
#include "Skill_Ground_A.generated.h"

/** 바닥에 스폰되어 범위 데미지 + 스폰 위치 기준에서 바깥쪽으로 튕겨(런치)됨
 * 
 */
UCLASS()
class PUSH_API ASkill_Ground_A : public AArea
{
	GENERATED_BODY()

public:
	ASkill_Ground_A();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		virtual void OnSkillClicked() override; // 스킬 버튼 누르기

	virtual void OnSpawnPointDecal(FVector InLocation) override;
	virtual void OnDestroy(FVector InLocation) override;

	void DestroyExplosion();

	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	class USkillComponent* SkillComponent;
	UPROPERTY(VisibleAnywhere)
		class USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere)
		class UProjectileMovementComponent* ProjectileComponent;
	UPROPERTY(EditAnywhere, Category = "Particle")
		class UParticleSystemComponent* Particle;

	UPROPERTY(EditAnywhere, Category = "Particle")
		class UParticleSystem* Explosion;
	UPROPERTY()
		class UParticleSystemComponent* ExplosionComponent;
	UPROPERTY(EditAnywhere, Category = "Particle")
		FVector ExplosionScale = FVector(1, 1, 1);
	UPROPERTY(EditAnywhere, Category = "PointDecal")
		TSubclassOf<class APointDecal> PointDecal_Class;

	UPROPERTY(EditAnywhere, Category = "DebugType")
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;

	TArray<ACharacter*> Hitted;
};

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Skill/Area/Area.h"
#include "Skill_Meteor_A.generated.h"

UCLASS(Blueprintable)
class PUSH_API ASkill_Meteor_A : public AArea
{
    GENERATED_BODY()

public:
    ASkill_Meteor_A();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaSeconds) override;

public:
    UFUNCTION(BlueprintCallable)
        virtual void OnSkillPressed() override;

    UFUNCTION(BlueprintCallable)
        virtual void OnSkillClicked() override;

    virtual void OnSpawnPointDecal(FVector InLocation) override;
    virtual void OnDestroy(FVector InLocation) override;

    UFUNCTION()
        void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
    UPROPERTY(VisibleAnywhere)
        class USphereComponent* SphereComponent;

    UPROPERTY(VisibleAnywhere)
        class UProjectileMovementComponent* ProjectileComponent;

    UPROPERTY(EditAnywhere, Category = "Particle")
        class UParticleSystemComponent* Particle;

    UPROPERTY(EditAnywhere, Category = "Particle")
        class UParticleSystem* Explosion;

    UPROPERTY(EditAnywhere, Category = "Particle")
        FVector ExplosionScale = FVector(1, 1, 1);

    UPROPERTY(EditAnywhere, Category = "PointDecal")
        TSubclassOf<class APointDecal> PointDecal_Class;

    UPROPERTY(EditAnywhere, Category = "DebugType")
        TEnumAsByte<ETraceTypeQuery> CollisionType;

    UPROPERTY(EditAnywhere, Category = "DebugType")
        TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;

    class USkillComponent* SkillComponent;

    TArray<ACharacter*> Hitted;
};
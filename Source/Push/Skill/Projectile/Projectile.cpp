#include "Skill/Projectile/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Global.h"

AProjectile::AProjectile()
{
	Helpers::CreateComponent(this, &Root, "Root");
	Helpers::CreateComponent(this, &Mesh, "Mesh", Root);
	Helpers::CreateComponent(this, &Collision, "Collision", Root);
	Helpers::CreateComponent(this, &Particle, "Particle", Root);

	Helpers::CreateActorComponent(this, &ProjectileComponent, "ProjectileComponent");
	Particle->SetIsReplicated(true);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(Datas.CanRotate == true)
	{
		// 231229 이민학
		// 방향 조절 Projectile 핵심코드
		if (!!Owner)
		{
			velocity = Owner->GetActorForwardVector() * ProjectileComponent->InitialSpeed;

			ProjectileComponent->Velocity = UKismetMathLibrary::VInterpTo(ProjectileComponent->Velocity, velocity, DeltaSeconds, Datas.InterpSpeed);
			SetActorRotation(UKismetMathLibrary::RInterpTo(GetActorRotation(), rotation, DeltaSeconds, Datas.InterpSpeed));
		}
	}
}

void AProjectile::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// 231229 이민학
	// 스피드, 중력값 초기화
	ProjectileComponent->InitialSpeed = 1000 * Datas.Speed;
	ProjectileComponent->ProjectileGravityScale = 1 * Datas.Gravity_Scale;
}

void AProjectile::OnDestroy()
{
}

void AProjectile::FOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}


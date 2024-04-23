#include "Skill_Fireball_P.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Character/PushCharacter.h"

ASkill_Fireball_P::ASkill_Fireball_P()
{
	bReplicates = true;
}

void ASkill_Fireball_P::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ASkill_Fireball_P::FOnBeginOverlap);
}

void ASkill_Fireball_P::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void ASkill_Fireball_P::FOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::FOnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	IDamageable* character = Cast<IDamageable>(OtherActor);
	APushCharacter* OwnerCharacter = Cast<APushCharacter>(OtherActor);

	if (character == nullptr || OwnerCharacter == Owner)
		return;
	
	character->Hit(this, HitData);
	
	OnDestroy();
}

void ASkill_Fireball_P::OnDestroy()
{
	Super::OnDestroy();

	// 231229 이민학
	// 폭발 파티클 소환, No Collision, 기존 Particle DeActive
	if (!!Explosion)
	{
		UParticleSystemComponent* particleComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, GetActorLocation());
		particleComponent->SetIsReplicated(true);
	}

	Particle->SetActive(false);
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
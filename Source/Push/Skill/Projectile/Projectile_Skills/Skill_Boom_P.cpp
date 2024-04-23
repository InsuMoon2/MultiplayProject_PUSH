#include "Skill_Boom_P.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Character/PushCharacter.h"

ASkill_Boom_P::ASkill_Boom_P()
{
	Helpers::CreateComponent(this, &DetectTarget, "DetectTarget", Root);
}

void ASkill_Boom_P::BeginPlay()
{
	Super::BeginPlay();

	if(SpawnParticle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAttached(SpawnParticle, Root);
	}

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ASkill_Boom_P::FOnBeginOverlap);
}

void ASkill_Boom_P::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(Target != nullptr)
	{
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation()));

		SetActorLocation(GetActorLocation() + GetActorForwardVector() * Speed);
	}
}

void ASkill_Boom_P::Destroyed()
{
	Super::Destroyed();

	if (!!Explosion)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, GetActorLocation());
	}
}

void ASkill_Boom_P::FOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::FOnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	APushCharacter* HittedActor = Cast<APushCharacter>(OtherActor);

	if(HittedActor != nullptr && HittedActor != GetOwner())
	{
		HittedActor->Hit(this, HitData);

		Destroy();
	}
}
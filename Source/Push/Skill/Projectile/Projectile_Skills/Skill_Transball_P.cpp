#include "Skill/Projectile/Projectile_Skills/Skill_Transball_P.h"
#include "Character/PushCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Global.h"

ASkill_Transball_P::ASkill_Transball_P()
{
}

void ASkill_Transball_P::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ASkill_Transball_P::FOnBeginOverlap);
}

void ASkill_Transball_P::FOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::FOnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	APushCharacter* HittedCharacter = Cast<APushCharacter>(OtherActor);
	APushCharacter* Ownertmp = Cast<APushCharacter>(Owner);

	if (Owner == nullptr || HittedCharacter == nullptr || HittedCharacter == Owner)
		return;

	CLog::Print(HittedCharacter);

	FVector OwnerLocation, HittedLocation;
	HittedLocation = HittedCharacter->GetActorLocation();
	OwnerLocation = Owner->GetActorLocation();

	Ownertmp->SetLocation(HittedLocation);
	HittedCharacter->SetLocation(OwnerLocation);

	if(TransParticle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAttached(TransParticle, HittedCharacter->GetMesh(), FName("Root"));
		UGameplayStatics::SpawnEmitterAttached(TransParticle, Ownertmp->GetMesh(), FName("Root"));
	}

	Destroy();
}
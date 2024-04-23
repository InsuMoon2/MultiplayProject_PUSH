#include "Skill/Area/AreaSkills/Skill_Mine_A.h"
#include "Components/CapsuleComponent.h"
#include "Global.h"
#include "Buffs/BuffInstance.h"
#include "Character/PushCharacter.h"
#include "Components/BuffComponent.h"
#include "Components/SkillComponent.h"
#include "Particles/ParticleSystemComponent.h"

ASkill_Mine_A::ASkill_Mine_A()
{
	//2024.01.15 이현중
	//감지 콜리전, 폭발범위 콜리전(감지되기 전에는 visibility = false)
	Helpers::CreateComponent<UCapsuleComponent>(this, &ActivationCollision, "ActivationCollision", Root);
	Helpers::CreateComponent<UCapsuleComponent>(this, &ExplosionCollision, "ExplosionCollision", Root);
	Helpers::CreateComponent<UParticleSystemComponent>(this, &BaseParticleComponent, "BaseParticleComponent", Root);
	Helpers::CreateComponent<UParticleSystemComponent>(this, &ExplosionParticleComponent, "ExplosionParticleComponent", Root);

	//폭발 파티클 종료후 엑터 제거함수 바인드
	ExplosionParticleComponent->SetVisibility(false);
	ExplosionParticleComponent->OnSystemFinished.AddDynamic(this, &ASkill_Mine_A::OnFinishParticle);
}

void ASkill_Mine_A::BeginPlay()
{
	Super::BeginPlay();

	USkillComponent* skillComponent = Helpers::GetComponent<USkillComponent>(Owner);
	if (!skillComponent)
		return;

	DecalLocation = skillComponent->SpawnLocation;

	ExplosionCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ActivationCollision->OnComponentBeginOverlap.AddDynamic(this, &ASkill_Mine_A::OnActivateOverlap);
	ExplosionCollision->OnComponentBeginOverlap.AddDynamic(this, &ASkill_Mine_A::OnExplosionOverlap);
	BaseParticleComponent->SetTemplate(BaseParticle);
}

//마인이 공격당했을때 폭파
void ASkill_Mine_A::Hit(AActor* InAttacker, const FHitData& InHitData)
{
	ActivationCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (ExplosionParticleComponent)
	{
		BaseParticleComponent->DestroyComponent(true);
		ExplosionParticleComponent->SetVisibility(true);
		ExplosionParticleComponent->SetTemplate(ExplosionParticle);
	}
}

//플레이어가 지뢰를 밟았을때
void ASkill_Mine_A::OnActivateOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Cast<IDamageable>(OtherActor) || OtherActor->IsA(StaticClass()))
		return;

	

	CLog::LogAndPrint(Cast<APushCharacter>(OtherActor)->CustomPlayerName);
	ActivationCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//DelayTime이후 ActiveExplosion함수(폭발 이펙트와 판정) 호출
	FTimerHandle tempTimer;
	GetWorldTimerManager().SetTimer(tempTimer, this, &ASkill_Mine_A::ActiveExplosion, DelayTime, false, DelayTime);
}

//폭발하는시기에 범위에 있는 적에게 디버프 부여
void ASkill_Mine_A::OnExplosionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (hitted.Find(OtherActor) >= 0 && hitted.Num() > 0)
		return;

	UBuffComponent* buffComponent = Helpers::GetComponent<UBuffComponent>(OtherActor);
	if (!buffComponent)
		return;

	buffComponent->AddBuff(BuffClass);
	hitted.AddUnique(OtherActor);
}

//폭발 파티클 끝난후 파괴
void ASkill_Mine_A::OnFinishParticle(class UParticleSystemComponent* PSystem)
{
	Destroy();
}

//정상적인 파티클 호출`
void ASkill_Mine_A::ActiveExplosion()
{
	ExplosionCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BaseParticleComponent->DestroyComponent(true);
	ExplosionParticleComponent->SetVisibility(true);
	ExplosionParticleComponent->SetTemplate(ExplosionParticle);
}

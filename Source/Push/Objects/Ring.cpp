#include "Objects/Ring.h"
#include "Global.h"
#include "Blueprint/UserWidget.h"
#include "Character/PushCharacter.h"
#include "Components/StateComponent.h"
#include "Widgets/WDG_EffectBase.h"
#include "HUD/MainHUD.h"
#include "Net/UnrealNetwork.h"

ARing::ARing()
{
	PrimaryActorTick.bCanEverTick = true;

	Helpers::CreateComponent<UCapsuleComponent>(this, &RingCapsule, "RingCapsule");
	Helpers::CreateComponent<UStaticMeshComponent>(this, &RingMesh, "RingMesh", RingCapsule);

	FString path = "StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'";
	RingMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(*path).Object);

	RingMesh->SetCollisionProfileName("OverlapAllDynamic");

	SetActorTickInterval(1.0f);
}

void ARing::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	TargetRadius = RingCapsule->GetUnscaledCapsuleRadius();
	Refresh();
}

void ARing::BeginPlay()
{
	Super::BeginPlay();

	RingCapsule->OnComponentBeginOverlap.AddDynamic(this, &ARing::OnBeginOverlap);
	RingCapsule->OnComponentEndOverlap.AddDynamic(this, &ARing::OnEndOverlap);
	StartRadius = RingCapsule->GetUnscaledCapsuleRadius();
}

void ARing::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void ARing::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARing, RingCapsule);
	DOREPLIFETIME(ARing, RingMesh);
}

void ARing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitData hitData;
	hitData.Damage = RingDamage;

	for(APushCharacter* character : OverlappedCharacters)
	{
		if (character == nullptr)
			continue;

		if(character->StateComponent->IsDeadMode())
			continue;

		character->Hit(this, hitData);

		APlayerController* controller = Cast<APlayerController>(character->GetController());

		if (controller == nullptr) continue;

		// Ring ¹Ù±ùÀÌ¸é È­¸é ±ô¹Ú°Å¸²
		AMainHUD* hud = Cast<AMainHUD>(controller->GetHUD());
		if (hud == nullptr) continue;
		if (hud->CheckWidget("Ring"))
		{
			hud->GetWidget<UWDG_EffectBase>("Ring")->PlayEffect();
		}
	}
}

void ARing::Shrink(float InRadius, float InTime)
{
	DeltaRadius = (RingCapsule->GetUnscaledCapsuleRadius() - InRadius) / (InTime * (float)100);
	TargetRadius = InRadius;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ARing::ChangeRadius, 0.01f, true, 0.0f);
}

void ARing::ChangeRadius()
{
	float radius = RingCapsule->GetUnscaledCapsuleRadius() - DeltaRadius;

	SetCapsuleRadius_NMC(radius);

	if (FMath::IsNearlyEqual(radius, TargetRadius))
		GetWorldTimerManager().ClearTimer(TimerHandle);

	float scale = radius / Base;
	RingMesh->SetWorldScale3D(FVector(scale, scale, scale * 100));
}

void ARing::Refresh()
{
	float radius = RingCapsule->GetUnscaledCapsuleRadius();
	RingCapsule->SetCapsuleRadius(radius);

	float scale = radius / Base;
	RingMesh->SetWorldScale3D(FVector(scale, scale, scale * 100));
}

void ARing::Reset()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);

	SetCapsuleRadius_NMC(StartRadius);

	float scale = StartRadius / Base;

	OverlappedCharacters.Empty();

	RingMesh->SetWorldScale3D(FVector(scale, scale, scale * 100));

}

void ARing::SetCapsuleRadius_NMC_Implementation(float InRadius)
{
	RingCapsule->SetCapsuleRadius(InRadius);
}

void ARing::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APushCharacter* character = Cast<APushCharacter>(OtherActor);

	if (character == nullptr)
		return;

	if(OverlappedCharacters.Contains(character))
		OverlappedCharacters.Remove(character);

}

void ARing::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APushCharacter* character = Cast<APushCharacter>(OtherActor);

	if (character == nullptr)
		return;

	OverlappedCharacters.AddUnique(character);
}


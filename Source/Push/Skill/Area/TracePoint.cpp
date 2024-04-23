#include "TracePoint.h"
#include "Components/DecalComponent.h"
#include "Global.h"

ATracePoint::ATracePoint()
{
	PrimaryActorTick.bCanEverTick = true;

	Helpers::CreateComponent(this, &Root, "Root", RootComponent);
	Helpers::CreateComponent(this, &TracePoint, "TracePoint", Root);

	TracePoint->SetVisibility(true);
	TracePoint->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
}

void ATracePoint::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = Cast<ACharacter>(GetOwner());

	if (Owner == nullptr)
		return;

}

void ATracePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO :: SkillData에서 껐다 켰다 할 수 있는 bool값 받아오기
	TraceDecal();

}

void ATracePoint::TraceDecal()
{
	// 231229_문인수
	// 카메라가 바라보는 방향에 Decal_Cursor Spawn

	FVector start;
	FRotator PlayerViewRotation;
	APlayerController* controller = Cast<APlayerController>(Owner->GetController());

	if (controller)
		controller->GetPlayerViewPoint(start, PlayerViewRotation);

	FVector direction = PlayerViewRotation.Vector();
	FVector end = start + (direction * MaxDistance);

	FHitResult HitResult;
	TArray<AActor*> ignores;
	ignores.Add(Owner);

	UKismetSystemLibrary::LineTraceSingle(Owner->GetWorld(), start, end, TraceType, false, ignores, DrawDebug_Decal, HitResult, true);

	// 최대 거리 전에 Hit 판정이 난다면, 아래로 한번 더 추적
	if (HitResult.bBlockingHit)
	{
		// Decal이 벽에 파고 들어가서 -direction 방향으로 위치 조절
		FVector DownStart = HitResult.ImpactPoint - (direction * 20.0f);
		FVector DownEnd = DownStart - FVector(0, 0, MaxDistance + 1000.0f);

		FHitResult DownHitResult;
		UKismetSystemLibrary::LineTraceSingle(Owner->GetWorld(), DownStart, DownEnd, TraceType, false, ignores, DrawDebug_Decal, DownHitResult, true);

		if (DownHitResult.bBlockingHit)
			TraceLocation = DownHitResult.ImpactPoint;

		else
			TraceLocation = HitResult.ImpactPoint;
	}

	// Decal Spawn 사정거리 제한
	// 최대 거리를 넘어가도 Hit가 안됐을 때는 최대거리 지점에 Decal Spawn
	else
	{
		FVector DownStart = end;
		FVector DownEnd = DownStart - FVector(0, 0, MaxDistance + 1000.0f);

		FHitResult DownHitResult;
		UKismetSystemLibrary::LineTraceSingle(Owner->GetWorld(), DownStart, DownEnd, TraceType, false, ignores, DrawDebug_Decal, DownHitResult, true);

		// 아래로 추적했을 때 Hit가 되면 그 지점에 Decal Spawn
		if (DownHitResult.bBlockingHit)
			TraceLocation = DownHitResult.ImpactPoint;

		// 그래도 Hit가 안되면 기존처럼 최대거리 지점에 Decal Spawn
		else
			TraceLocation = end;

	}

	TracePoint->SetWorldLocation(TraceLocation);
}


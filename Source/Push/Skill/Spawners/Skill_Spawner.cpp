#include "Skill/Spawners/Skill_Spawner.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Skill/Skill.h"
#include "Global.h"
#include "Components/BoxComponent.h"

ASkill_Spawner::ASkill_Spawner()
{
	Helpers::CreateComponent(this, &Root, "Root");
	Helpers::CreateComponent(this, &SpawnBox, "SpawnBox", Root);
}

void ASkill_Spawner::BeginPlay()
{
	Super::BeginPlay();

	if(SpawnedSkill != nullptr)
	{
		for(int i = 0; i < LoopCount; i++)
		{
			FActorSpawnParameters params;
			params.Owner = Owner;
			params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			FVector SpawnPoint = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), SpawnBox->GetScaledBoxExtent());
			GetWorld()->SpawnActor<ASkill>(SpawnedSkill, SpawnPoint, FRotator::ZeroRotator, params);
		}
	}

	Destroy();
}

void ASkill_Spawner::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

#include "Skill.h"
#include "Components/ShapeComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"

ASkill::ASkill()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASkill::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());

	if (!Owner)
	{
		return;
	}
	

}

void ASkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}



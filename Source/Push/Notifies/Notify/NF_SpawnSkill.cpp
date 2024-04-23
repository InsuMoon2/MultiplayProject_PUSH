#include "Notifies/Notify/NF_SpawnSkill.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/SkillComponent.h"
#include "Skill/Skill.h"
#include "Skill/SkillData.h"
#include "Skill/SkillDatas/SkillData_Projectile.h"

FString UNF_SpawnSkill::GetNotifyName_Implementation() const
{
	return "Spawn_Skill";
}

void UNF_SpawnSkill::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACharacter* Owner = Cast<ACharacter>(MeshComp->GetOwner());
	if (Owner == nullptr || Owner->HasAuthority() == true)
		return;

	USkillComponent* SkillComponent = Helpers::GetComponent<USkillComponent>(Owner);

	if (SkillComponent == nullptr)
		return;

	FVector SpawnLocation, RelativeSpawnLocation;
	FRotator SpawnRotation;

	if (SkillComponent->curSkillData == nullptr)
	{
		return;
	}

	TSubclassOf<ASkill> SpawnSkill = SkillComponent->curSkillData->Skill;

	USkillData_Projectile* SkillData = Cast<USkillData_Projectile>(SkillComponent->curSkillData);
	// Projectile
	if (SkillData != nullptr)

	{
		SpawnLocation = Owner->GetActorLocation() + Owner->GetActorForwardVector() * SkillComponent->curSkillData->RelativeDistance;
		SpawnRotation = Owner->GetActorForwardVector().Rotation();
	}
	// Area
	else
	{
		SpawnLocation = SkillComponent->SpawnLocation;
		SpawnRotation = Owner->GetActorForwardVector().Rotation();
	}


	FActorSpawnParameters params;
	params.Owner = Owner;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Owner->GetWorld()->SpawnActor<ASkill>(SpawnSkill, SpawnLocation, SpawnRotation, params);

	//if(controller == Owner->GetWorld()->GetFirstPlayerController())
		//SkillComponent->SpawnCallOnServer_Implementation(controller, SpawnSkill, SpawnLocation, SpawnRotation);

	//	SkillComponent->SpawnCallOnServer_Implementation(SpawnSkill, SpawnLocation, SpawnRotation);
}
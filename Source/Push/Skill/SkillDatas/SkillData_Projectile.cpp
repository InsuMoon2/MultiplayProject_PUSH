#include "Skill/SkillDatas/SkillData_Projectile.h"
#include "GameFramework/Character.h"
#include "Character/PushCharacter.h"
#include "Global.h"
#include "Components/SkillComponent.h"
#include "Components/StateComponent.h"


void USkillData_Projectile::Play(ACharacter* InOwner)
{
	Super::Play(InOwner);

	APushCharacter* character = Cast<APushCharacter>(InOwner);

	if (character == nullptr)
		return;

	USkillComponent* skillComponent = Helpers::GetComponent<USkillComponent>(InOwner);

	if (skillComponent == nullptr)
		return;

	skillComponent->SpawnLocation = character->GetActorLocation();
	// character->SetSpawnlocationRep(skillComponent->SpawnLocation);

	character->PlayAnimMontage(Product.ActionMontage, Product.PlayRate);
}

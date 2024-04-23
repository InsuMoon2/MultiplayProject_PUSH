#include "Buffs/BuffInstance_DotDamage.h"
#include "Components/ResourceComponent.h"
#include "Global.h"

void ABuffInstance_DotDamage::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	DotPlayTime += DeltaSeconds;
	if(DotPlayTime > DotDelay)
	{
		DotPlayTime -= DotDelay;
		Active();
	}
}

void ABuffInstance_DotDamage::Active()
{
	if (!Owner.IsValid())
		return;
	 
	UResourceComponent* resourceComponent = Helpers::GetComponent<UResourceComponent>(Owner.Get());

	if (!resourceComponent)
		return;

	if(HasAuthority())	
		resourceComponent->AdjustHP(-Damage);
}

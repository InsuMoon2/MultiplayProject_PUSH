#include "Buffs/BuffInstance_Healing.h"

#include "Components/ResourceComponent.h"
#include "Utilites/Helpers.h"

void ABuffInstance_Healing::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	healPlayTime += DeltaSeconds;
	if (healPlayTime > HealDelay)
	{
		healPlayTime -= HealDelay;
		Active();
	}
}

void ABuffInstance_Healing::Active()
{
	if (!Owner.IsValid())
		return;

	UResourceComponent* resourceComponent = Helpers::GetComponent<UResourceComponent>(Owner.Get());

	if (!resourceComponent)
		return;

	if (HasAuthority())
		resourceComponent->AdjustHP(Restoration);
}

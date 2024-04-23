#include "Items/Item_BuffSelf.h"
#include "Global.h"
#include "Buffs/BuffInstance.h"
#include "Components/BuffComponent.h"

void AItem_BuffSelf::BeginPlay()
{
	AItemBase::BeginPlay();

}

void AItem_BuffSelf::Tick(float DeltaTime)
{
	AItemBase::Tick(DeltaTime);
}

void AItem_BuffSelf::UseItem_Implementation()
{
	Super::UseItem_Implementation();
	if (!Owner.IsValid())
		return;

	UBuffComponent* buffComponent = Helpers::GetComponent<UBuffComponent>(Owner.Get());


	if (!!buffComponent)
	{
		buffComponent->AddBuff(BuffClass);
		Destroy();
	}
}


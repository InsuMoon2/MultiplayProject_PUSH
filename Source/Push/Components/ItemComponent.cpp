
#include "Components/ItemComponent.h"
#include "Items/ItemBase.h"
#include "Global.h"
#include "Items/Item_BuffSelf.h"

UItemComponent::UItemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UItemComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<ACharacter>(GetOwner());
}


void UItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UItemComponent::UseItem(TSubclassOf<AItemBase> ItemClass)
{
	UseItem_Server(ItemClass);
}

void UItemComponent::UseItem_Server_Implementation(TSubclassOf<AItemBase> ItemClass)
{
	UseItem_NMC(ItemClass);
}

//아이템 사용
void UItemComponent::UseItem_NMC_Implementation(TSubclassOf<AItemBase> ItemClass)
{
	if (!Owner.IsValid() || !ItemClass)
		return;

	FActorSpawnParameters param;
	param.Owner = Owner.Get();
	Item = Cast<AItemBase>(Owner->GetWorld()->SpawnActor(ItemClass, 0, 0, param));
	
	if (!Item.IsValid())
		return;

	Item->UseItem();
}

void UItemComponent::DestroyItem()
{
	if (!Item.IsValid())
		return;
	Item->Destroy();
}

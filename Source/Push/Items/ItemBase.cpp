#include "Items/ItemBase.h"
#include "Global.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "PhysicalMaterials/PhysicalMaterial.h"


AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());
}

void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBase::UseItem_Implementation()
{
}

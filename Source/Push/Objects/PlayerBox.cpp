#include "Objects/PlayerBox.h"
#include "Utilites/Helpers.h"
#include "Components/BoxComponent.h"

APlayerBox::APlayerBox()
{
	Helpers::CreateComponent<USceneComponent>(this, &Root, "Root");
}

void APlayerBox::BeginPlay()
{
	Super::BeginPlay();

	TArray<USceneComponent*> children;
	Root->GetChildrenComponents(true, children);

	for(USceneComponent* child : children)
	{
		UBoxComponent* box = Cast<UBoxComponent>(child);

		if (box == nullptr)
			continue;

		Boxes.Push(box);
	}
}

void APlayerBox::ToggleCollision_NMC_Implementation(bool InBool)
{
	for(UBoxComponent* box : Boxes)
	{
		if (InBool)
			box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		else
			box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

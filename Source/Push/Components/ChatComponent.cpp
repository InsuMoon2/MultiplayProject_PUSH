#include "Components/ChatComponent.h"

UChatComponent::UChatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	
}

void UChatComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UChatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}


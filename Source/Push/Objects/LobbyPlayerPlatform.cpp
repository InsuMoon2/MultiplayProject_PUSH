#include "Objects/LobbyPlayerPlatform.h"
#include "Global.h"
#include "Character/PushCharacter.h"
#include "Components/ArrowComponent.h"

ALobbyPlayerPlatform::ALobbyPlayerPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	Helpers::CreateComponent(this, &Root, "Root", GetRootComponent());
	Helpers::CreateComponent(this, &Cube, "Cube", Root);
	Helpers::CreateComponent(this, &PlayerSpawnTransform, "PlayerSpawnTransform", Root);
}

void ALobbyPlayerPlatform::BeginPlay()
{
	Super::BeginPlay();

	
}

void ALobbyPlayerPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALobbyPlayerPlatform::SpawnCharacter_Implementation(APlayerController* InPlayerController)
{

}

void ALobbyPlayerPlatform::Clear_Implementation()
{

}
#include "Objects/LobbyPawn.h"
#include "Global.h"
#include "Camera/CameraComponent.h"

ALobbyPawn::ALobbyPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	Helpers::CreateComponent(this, &Root, "Root", GetRootComponent());
	Helpers::CreateComponent(this, &Camera, "Camera", Root);

	Camera->SetFieldOfView(60.0f);
}

void ALobbyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALobbyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALobbyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


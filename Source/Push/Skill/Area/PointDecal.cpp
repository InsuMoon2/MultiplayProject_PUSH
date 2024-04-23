#include "PointDecal.h"
#include "Components/DecalComponent.h"
#include "Global.h"

APointDecal::APointDecal()
{
	PrimaryActorTick.bCanEverTick = true;

	Helpers::CreateComponent(this, &Root, "Root", RootComponent);
	Helpers::CreateComponent(this, &PointDecal, "PointDecal", Root);
	PointDecal->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	PointDecal->SetVisibility(true);

	PointDecal->DecalSize = FVector(10,128,128);
}

void APointDecal::BeginPlay()
{
	Super::BeginPlay();

	Dynamic = PointDecal->CreateDynamicMaterialInstance();
	PointDecal->SetDecalMaterial(Dynamic);

}

void APointDecal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}


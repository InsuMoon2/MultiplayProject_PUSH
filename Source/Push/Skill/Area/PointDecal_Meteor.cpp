#include "PointDecal_Meteor.h"
#include "Components/DecalComponent.h"

APointDecal_Meteor::APointDecal_Meteor()
{

}

void APointDecal_Meteor::BeginPlay()
{
	Super::BeginPlay();

	CurrentTime = 0.0f;
	InterpSpeed = MaxRadius / DecalTime;
}

void APointDecal_Meteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentTime += DeltaTime;

	if (CurrentTime <= DecalTime)
	{
		Radius = FMath::Min(Radius + InterpSpeed * DeltaTime, MaxRadius);
		Dynamic->SetScalarParameterValue("Radius", Radius);
	}

	else
	{
		PointDecal->SetVisibility(false);
		Destroy();
	}

}

void APointDecal_Meteor::SetDecalTime(float InDecalTime)
{
	Super::SetDecalTime(InDecalTime);

	DecalTime = InDecalTime;
}

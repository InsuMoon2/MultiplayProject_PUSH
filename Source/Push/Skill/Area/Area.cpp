#include "Area.h"
#include "Global.h"
#include "GameFramework/Character.h"

AArea::AArea()
{
	bReplicates = true;

	Helpers::CreateComponent(this, &Root, "Root", RootComponent);

}

void AArea::BeginPlay()
{
	Super::BeginPlay();


}

void AArea::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


}

void AArea::OnSkillPressed()
{
	Super::OnSkillPressed();


}

void AArea::OnSkillClicked()
{
	Super::OnSkillClicked();


}
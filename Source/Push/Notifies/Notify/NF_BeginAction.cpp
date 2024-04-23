#include "Notifies/Notify/NF_BeginAction.h"

#include "Components/MoveComponent.h"
#include "Components/StateComponent.h"
#include "Utilites/Helpers.h"

FString UNF_BeginAction::GetNotifyName_Implementation() const
{
	return "Begin_Action";
}

void UNF_BeginAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;

	UMoveComponent* move = Helpers::GetComponent<UMoveComponent>(MeshComp->GetOwner());
	UStateComponent* state = Helpers::GetComponent<UStateComponent>(MeshComp->GetOwner());

	if (move == nullptr) return;
	if (state == nullptr) return;

	if (bMoveCheck == false)
		move->Stop();

	else
		move->Move();

	state->BeginAction();

	
}


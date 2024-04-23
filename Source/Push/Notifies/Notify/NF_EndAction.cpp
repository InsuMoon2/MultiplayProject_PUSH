#include "Notifies/Notify/NF_EndAction.h"
#include "Global.h"
#include "Components/MoveComponent.h"
#include "Components/StateComponent.h"

FString UNF_EndAction::GetNotifyName_Implementation() const
{
	return "End_Action";
}

void UNF_EndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;

	UMoveComponent* move = Helpers::GetComponent<UMoveComponent>(MeshComp->GetOwner());
	UStateComponent* state = Helpers::GetComponent<UStateComponent>(MeshComp->GetOwner());

	if (move == nullptr) return;
	if (state == nullptr) return;

	if (move->CanMove() == false)
	{
		move->Move();
	}

	state->EndAction();


}

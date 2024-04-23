#include "Components/StateComponent.h"
#include "GameFramework/Character.h"

UStateComponent::UStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	
}

void UStateComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());
}

void UStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UStateComponent::BeginAction()
{
	bInAction = true;
	SetActionMode();
}

void UStateComponent::EndAction()
{
	bInAction = false;
	SetIdleMode();
}

void UStateComponent::SetIdleMode()
{
	if (Owner->IsLocallyControlled())
		ChangeType_Server(EStateType::ES_Idle);
}

void UStateComponent::SetActionMode()
{
	if(Owner->IsLocallyControlled())
		ChangeType_Server(EStateType::ES_Action);
}

void UStateComponent::SetHittedMode()
{
	if (Owner->IsLocallyControlled())
		ChangeType_Server(EStateType::ES_Hitted);
}

void UStateComponent::SetDeadMode()
{
	if (Owner->IsLocallyControlled())
		ChangeType_Server(EStateType::ES_Dead);
}

bool UStateComponent::IsDeadMode()
{
	return StateType == EStateType::ES_Dead;
}

void UStateComponent::ChangeType_NMC_Implementation(EStateType InType)
{
	EStateType prevType = StateType;
	StateType = InType;

	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Broadcast(prevType, StateType);
}

void UStateComponent::ChangeType_Server_Implementation(EStateType InType)
{
	ChangeType_NMC(InType);
}


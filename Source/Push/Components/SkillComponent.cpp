#include "Components/SkillComponent.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Skill/SkillData.h"
#include "Skill/Skill.h"
#include "Skill/SkillDatas/SkillData_Projectile.h"
#include "Global.h"

USkillComponent::USkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());

	
}


void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void USkillComponent::UseSkill(TSubclassOf<USkillData> SkillData)
{
	if (SkillData != nullptr)
	{
		SetCurSkillData_Server(SkillData);
	}
}

void USkillComponent::Execute()
{
	if(curSkillData != nullptr)
	{
		curSkillData->Play(Owner);
	}
}

void USkillComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USkillComponent, SpawnLocation);
}

void USkillComponent::SetCurSkillData_Server_Implementation(TSubclassOf<class USkillData> SkillData)
{
	SetCurSkillData_NMC(SkillData);
}

void USkillComponent::SetCurSkillData_NMC_Implementation(TSubclassOf<class USkillData> SkillData)
{
	if (SkillData != nullptr)
	{
		prevSkillData = curSkillData;
		curSkillData = NewObject<USkillData>(Owner, SkillData);

		if (prevSkillData != nullptr)
		{
			if (prevSkillData->IsA(SkillData))
			{
				curSkillData = prevSkillData;
			}
			else
			{
				prevSkillData->Destroy_TracePoint();
			}
		}
	}

	Execute();

	if (OnCoolDown.IsBound() == true)	OnCoolDown.Broadcast();
}


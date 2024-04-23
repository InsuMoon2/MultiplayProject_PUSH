#include "Buffs/BuffInstance_Freezing.h"

#include "GameFramework/Character.h"
#include "Components/MoveComponent.h"
#include "Global.h"
#include "Character/AnimInstance_PushCharacter.h"
#include "Components/BuffComponent.h"
#include "Widgets/WDG_BuffBoard.h"


void ABuffInstance_Freezing::BeginPlay()
{
    AActor::BeginPlay();
    Owner = Cast<ACharacter>(GetOwner());

    if (!Owner.IsValid())
        return;


    OnEffect();

    APlayerController* controller = Cast<APlayerController>(Owner->GetController());
    UBuffComponent* buffComponent = Helpers::GetComponent<UBuffComponent>(Owner.Get());
    if (!controller || !buffComponent)
        return;

    if (controller->IsLocalController() && !!HasAuthority())
    {
        //버프 위젯 생성
        Widget = CreateWidget<UWDG_Buff>(controller, WidgetClass, "BuffWidget" + buffComponent->BuffCount++);
        Widget->SetBuffUI(UIImage, &PlayTime, &LifeTime);
        Widget->AddToViewport();

        buffComponent->Widget->AddBuff(Widget);
    }
}

void ABuffInstance_Freezing::OnEffect()
{
    Super::OnEffect();

    FreezeON_Server();
}

void ABuffInstance_Freezing::OffEffect()
{
    Super::OffEffect();
    FreezeOFF_Server();
}

void ABuffInstance_Freezing::FreezeOFF_Server_Implementation()
{
    FreezeOFF_NMC();
}

void ABuffInstance_Freezing::FreezeOFF_NMC_Implementation()
{
    UMoveComponent* MoveComponent = Helpers::GetComponent<UMoveComponent>(Owner.Get());
    UAnimInstance_PushCharacter* AnimInstance = Cast<UAnimInstance_PushCharacter>(Owner->GetMesh()->GetAnimInstance());
    if (!MoveComponent)
        return;

    MoveComponent->Move();

    if (AnimInstance == nullptr)
        return;

    AnimInstance->IsSnapshot = false;
}

void ABuffInstance_Freezing::FreezeON_Server_Implementation()
{
    FreezeON_NMC();
}

void ABuffInstance_Freezing::FreezeON_NMC_Implementation()
{
    CLog::Log("NMC_Freezing");
    if (!Owner.IsValid())
        return;
    UMoveComponent* MoveComponent = Helpers::GetComponent<UMoveComponent>(Owner.Get());
    UAnimInstance_PushCharacter* AnimInstance = Cast<UAnimInstance_PushCharacter>(Owner->GetMesh()->GetAnimInstance());
    if (!MoveComponent)
        return;
    MoveComponent->Stop();
    if (!AnimInstance)
        return;

    AnimInstance->SavePoseSnapshot("Freezing");
    AnimInstance->IsSnapshot = true;
}

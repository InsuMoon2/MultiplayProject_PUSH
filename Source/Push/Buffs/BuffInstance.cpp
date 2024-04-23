#include "BuffInstance.h"

#include "BuffInstance_Freezing.h"
#include "Components/BuffComponent.h"
#include "Widgets/WDG_Buff.h"
#include "Global.h"
#include "Widgets/WDG_BuffBoard.h"

ABuffInstance::ABuffInstance()
{
	PrimaryActorTick.bCanEverTick = true;

	FString path = "WidgetBlueprint'/Game/BP/Widgets/BuffWidget/WDG_Buff.WDG_Buff_C'";

	WidgetClass = ConstructorHelpers::FClassFinder<UWDG_Buff>(*path).Class;
	bReplicates = true;
}

ABuffInstance::~ABuffInstance()
{
}

void ABuffInstance::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<ACharacter>(GetOwner());

	if (!Owner.IsValid())
		return;

	APlayerController* controller = Cast<APlayerController>(Owner->GetController());
	UBuffComponent* buffComponent = Helpers::GetComponent<UBuffComponent>(Owner.Get());
	if (!controller || !buffComponent)
		return;

	if (controller->IsLocalController())
	{
		OnEffect();
	}

	if (controller->IsLocalController() && !HasAuthority())
	{
		return;
	}
	if (controller->IsLocalController())
	{
		//버프 위젯 생성
		Widget = CreateWidget<UWDG_Buff>(controller, WidgetClass, "BuffWidget" + buffComponent->BuffCount++);
		Widget->SetBuffUI(UIImage, &PlayTime, &LifeTime);
		Widget->AddToViewport();

		buffComponent->Widget->AddBuff(Widget);
	}
}

void ABuffInstance::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//2024.01.08 이현중
	//버프의 시간진행, 지속시간이 끝날시 제거
	PlayTime += DeltaSeconds;
	if (PlayTime > LifeTime)
	{
		if (!Owner.IsValid())
		{
			CLog::Print("buffInstanceError");
			return;
		}

		UBuffComponent* buffComponent = Helpers::GetComponent<UBuffComponent>(Owner.Get());
		if(!buffComponent)
		{
			CLog::Print("buffInstanceError");
			return;
		}
		buffComponent->RemoveBuff(this);

		APlayerController* controller = Cast<APlayerController>(Owner->GetController());
		if (!HasAuthority())
		{
			if (!!controller && controller->IsLocalController())
			{
				if (!!Widget)
				{
					Widget->RemoveFromParent();
				}
				OffEffect();
				DestroySelf_Server();
				Destroy();
			}
			else
			{
				OffEffect();
				Destroy();
			}
		}
		else
		{
			OffEffect();
			Destroy();
		}
	}
}

void ABuffInstance::DestroySelf_Server_Implementation()
{
	Destroy();
}

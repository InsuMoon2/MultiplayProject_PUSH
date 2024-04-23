#include "HUD/MainHUD.h"
#include "HUD/Resource.h"
#include "Widgets/WDG_EffectBase.h"
#include "Widgets/StoreUI.h"
#include "Widgets/KillDeathUI.h"
#include "Global.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	//AddEffectWidget();
}

void AMainHUD::DrawHUD()
{
	Super::DrawHUD();

}

void AMainHUD::AddWidget()
{
	TWeakObjectPtr<APlayerController> PlayerController = GetOwningPlayerController();

	if (UserWidgetClasses.Num() == 0 || !PlayerController.IsValid())
		return;

	for (TPair<FString, TSubclassOf<UUserWidget>> widgetClass : UserWidgetClasses)
	{
		if (IsValid(widgetClass.Value))
		{
			UUserWidget* temp = CreateWidget<UUserWidget>(PlayerController.Get(), widgetClass.Value);
			temp->AddToViewport(); //
			UserWidgets.Add(widgetClass.Key, temp);
		}
	}
}

bool AMainHUD::CheckWidget(const FString& widgetname)
{
	if (false == UserWidgets.Contains(widgetname))
		return false;

	return true;
}
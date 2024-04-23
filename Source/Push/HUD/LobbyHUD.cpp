#include "HUD/LobbyHUD.h"
#include "Global.h"
#include "Blueprint/UserWidget.h"

void ALobbyHUD::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALobbyHUD::DrawHUD()
{
	Super::DrawHUD();

}

void ALobbyHUD::AddWidget()
{
	TWeakObjectPtr<APlayerController> PlayerController = GetOwningPlayerController();

	if (UserWidgetClasses.Num() == 0 || !PlayerController.IsValid())
		return;

	for (TPair<FString, TSubclassOf<UUserWidget>> widgetClass : UserWidgetClasses)
	{
		if (IsValid(widgetClass.Value))
		{
			UUserWidget* temp = CreateWidget<UUserWidget>(PlayerController.Get(), widgetClass.Value);
			temp->AddToViewport(-1); 
			UserWidgets.Add(widgetClass.Key, temp);
		}
	}
}

bool ALobbyHUD::CheckWidget(const FString& widgetname)
{
	if (false == UserWidgets.Contains(widgetname))
		return false;

	return true;
}
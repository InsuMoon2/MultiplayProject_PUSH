#include "Components/ShopComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "HUD/MainHUD.h"
#include "PlayerController/PushPlayerController.h"
#include "Widgets/StoreUI.h"
#include "Widgets/MainUI.h"

UShopComponent::UShopComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UShopComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<ACharacter>(GetOwner());

	PlayerController = Cast<APushPlayerController>(Owner->GetController());
	if(PlayerController != nullptr)
	{
		if(PlayerController->GetHUD() != nullptr)
			MainHUD = Cast<AMainHUD>(PlayerController->GetHUD());
	}
}


void UShopComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UShopComponent::OpenStoreUI()
{
	if (Owner == nullptr || PlayerController == nullptr || MainHUD == nullptr)
		return;

	if (MainHUD->CheckWidget("Main") == true)
		MainUI = MainHUD->GetWidget<UMainUI>("Main");

	MainUI->OpenStoreUI();
}

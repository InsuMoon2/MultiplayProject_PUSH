#include "Widgets/StartMenuUI.h"
#include "Components/Button.h"
//
//bool UStartMenuUI::Initialize()
//{
//	if(false == Super::Initialize())
//	{
//		return false;
//	}
//
//	if(IsValid(JoinButton))
//	{
//		JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
//	}
//
//	return true;
//}
//
//void UStartMenuUI::JoinButtonClicked()
//{
//	TWeakObjectPtr<UGameInstance> GameInstance = GetGameInstance();
//	if (GameInstance.IsValid())
//	{
//		TWeakObjectPtr<UWorld> World = GetWorld();
//		if (World.IsValid())
//		{
//			World->ServerTravel(FString("/Game/SW/Maps/TestLevelMap"));
//		}
//	}
//}

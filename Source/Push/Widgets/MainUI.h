#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"

UCLASS()
class PUSH_API UMainUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
		void OpenStoreUI();
		void OpenStoreUI_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void Add_KillFeed(const FString& InKillPlayer, const FString& InDeadPlayer);

public:
	void GetSkillSlots();
};

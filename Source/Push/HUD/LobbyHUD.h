#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LobbyHUD.generated.h"

UCLASS()
class PUSH_API ALobbyHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;
	void AddWidget();
	bool CheckWidget(const FString& widgetname);

	template<class T>
	T* GetWidget(FString Key);

	UPROPERTY(EditAnywhere, Category = "Widgets")
		TMap<FString, TSubclassOf<class UUserWidget>> UserWidgetClasses;

	UPROPERTY()
		TMap<FString, class UUserWidget*> UserWidgets;

protected:
	virtual void BeginPlay() override;
};

template <class T>
T* ALobbyHUD::GetWidget(FString Key)
{
	if (false == UserWidgets.Contains(Key)) return nullptr;

	T* temp = Cast<T>((*(UserWidgets.Find(Key))));

	return temp;
}

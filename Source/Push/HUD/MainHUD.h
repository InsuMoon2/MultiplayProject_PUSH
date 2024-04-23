#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/HUD.h"
#include "Utilites/CLog.h"
#include "MainHUD.generated.h"

/** UserWidget들을 통합하여 관리하는 HUD 클래스
 *  HUD는 GameMode에 등록된다.
 */

UCLASS()
class PUSH_API AMainHUD : public AHUD
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

	UPROPERTY(BlueprintReadWrite)
		TMap<FString, class UUserWidget*> UserWidgets;

protected:
	virtual void BeginPlay() override;
};

template <class T>
T* AMainHUD::GetWidget(FString Key)
{
	if (false == UserWidgets.Contains(Key)) return nullptr;

	T* temp = Cast<T>((*(UserWidgets.Find(Key))));

	if (temp == nullptr)
	{
		CLog::Print("WRONG_NAME_WIDGET_" + Key);
		return nullptr;
	}
	return temp;
}
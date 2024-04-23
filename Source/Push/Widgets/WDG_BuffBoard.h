#pragma once

#include "CoreMinimal.h"
#include "WDG_Buff.h"
#include "Blueprint/UserWidget.h"
#include "WDG_BuffBoard.generated.h"

/*TODO : 2024.01.05 이현중
  그리드 위젯 안에 추가
*/

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnRemoveChild, UWDG_Buff*, widget);

UCLASS()
class PUSH_API UWDG_BuffBoard : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
public:
	UFUNCTION(BlueprintImplementableEvent)
		void AddBuff(UWDG_Buff* widget);

	UFUNCTION(BlueprintImplementableEvent)
		void OnRemoveChild(UWDG_Buff* widget);

	UFUNCTION()
		void SubWidget(UWDG_Buff* widget);


public:
	//2024.01.09 이현중
	//버프가 제거됐을때 실행할 델리게이트
	FOnRemoveChild RemoveChildDelegate;
};

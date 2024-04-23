#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WDG_BuffBase.generated.h"

/*TODO : 2024.01.05 이현중
  그리드 위젯 안에 추가
*/

UCLASS()
class PUSH_API UWDG_BuffBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void AddBuff();
};

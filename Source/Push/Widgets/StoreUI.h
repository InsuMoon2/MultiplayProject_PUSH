#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StoreUI.generated.h"

/** 상점 UI: 아이템 구입, 판매 등의 작업을 하는 UI
 * 
 */
UCLASS(Blueprintable)
class PUSH_API UStoreUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UStoreUI(const FObjectInitializer& ObjectInitializer);
		
};
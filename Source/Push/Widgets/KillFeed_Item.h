#pragma once

#include "CoreMinimal.h"
#include "WDG_EffectBase.h"
#include "Blueprint/UserWidget.h"
#include "KillFeed_Item.generated.h"

UCLASS()
class PUSH_API UKillFeed_Item : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void PlayEffect();
	
};

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerNameTag.generated.h"

UCLASS()
class PUSH_API UPlayerNameTag : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void SetPlayerName(const FString& InPlayerName);
};

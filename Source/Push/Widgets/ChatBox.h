#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatBox.generated.h"

UCLASS()
class PUSH_API UChatBox : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void FocusChat();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void ExitChat();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Scroll(bool InUp);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void AddChatMessage(const FString& InMessage);

	UPROPERTY(BlueprintReadWrite)
		bool bChatFocuse;

	UPROPERTY(BlueprintReadWrite)
		float ScrollMultiplier = 60.0f;
};

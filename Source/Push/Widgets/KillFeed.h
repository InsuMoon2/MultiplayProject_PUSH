#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Misc/Structures.h"
#include "KillFeed.generated.h"

UCLASS()
class PUSH_API UKillFeed : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Add_Killfeed(const FString& InKillPlayer, const FString& InDeadPlayer);
	
};

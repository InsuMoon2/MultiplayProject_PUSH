#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Misc/Structures.h"
#include "LeaderBoard_List.generated.h"

UCLASS(Blueprintable)
class PUSH_API ULeaderBoard_List : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void UpdatePlayerData(FPlayerList InPlayerData);

};

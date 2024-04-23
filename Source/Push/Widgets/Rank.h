#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Rank.generated.h"

UCLASS()
class PUSH_API URank : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* RankText;
};

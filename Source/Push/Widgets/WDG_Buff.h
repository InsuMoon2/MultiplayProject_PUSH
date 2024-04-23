#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WDG_Buff.generated.h"

UCLASS()
class PUSH_API UWDG_Buff : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetBuffUI(UTexture2D* image, float* playTime, float* lifeTime);
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(BlueprintReadOnly)
		UTexture2D* UIImage;

	float* PlayTime;
	float* LifeTime;

	UPROPERTY(BlueprintReadOnly)
		float TimePercent;
};

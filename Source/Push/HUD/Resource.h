#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Resource.generated.h"

/** 캐릭터의 상태(체력, 점수 등)을 보여주는 UserWidget 클래스
 * 
 */

UCLASS(Blueprintable)
class PUSH_API UResource : public UUserWidget
{
	GENERATED_BODY()

public:
	UResource(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar; // 체력 바

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MatchStateTypeText; 
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MatchCountdownText; // 시간
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* GoldText;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* KillText;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* DeathText;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* GameText;
};

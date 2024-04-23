#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class PUSH_API UStartMenuUI : public UUserWidget
{
	GENERATED_BODY()

public:

protected:
	//virtual bool Initialize() override;

private:
	//UFUNCTION()
	//void JoinButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;
};

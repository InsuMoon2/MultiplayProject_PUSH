#pragma once

#include "CoreMinimal.h"
#include "Widgets/WDG_Buff.h"
#include "BuffInstance.generated.h"

UCLASS()
class PUSH_API ABuffInstance : public AActor
{
	GENERATED_BODY()

public:
	friend class UBuffComponent;
	ABuffInstance();
	 ~ABuffInstance();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	UWDG_Buff* GetWidget() { return Widget; }

public:
	UFUNCTION()
		virtual void OnEffect(){}
	UFUNCTION()
		virtual void OffEffect(){}

	UFUNCTION(Reliable, Server)
		void DestroySelf_Server();
protected:
	TWeakObjectPtr<ACharacter> Owner = nullptr;

	UPROPERTY(EditAnywhere)
		UTexture2D* UIImage;

	UPROPERTY()
		TSubclassOf<class UWDG_Buff> WidgetClass;

	class UWDG_Buff* Widget;

	UPROPERTY(EditAnywhere)
		float LifeTime;

	float PlayTime = 0;
};

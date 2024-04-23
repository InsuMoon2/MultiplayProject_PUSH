#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "Item_BuffSelf.generated.h"

UCLASS(Blueprintable)
class PUSH_API AItem_BuffSelf : public AItemBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void UseItem_Implementation() override;

private:
	UPROPERTY(EditAnywhere, Category = "BuffClass")
		TSubclassOf<class ABuffInstance> BuffClass;
};

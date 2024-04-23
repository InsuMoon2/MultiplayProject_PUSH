#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Item_DotItem.generated.h"

UCLASS()
class PUSH_API AItem_DotItem : public AItemBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	virtual void UseItem_Implementation() override;


private:
	UPROPERTY(EditAnywhere, Category = "BuffClass")
		TSubclassOf<class ABuffInstance> BuffClass;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<ETraceTypeQuery> TraceType;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<EDrawDebugTrace::Type> DrawType;
};

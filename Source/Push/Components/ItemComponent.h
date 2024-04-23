#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PUSH_API UItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UItemComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable)
		void UseItem(TSubclassOf<class AItemBase> ItemClass);
	
	UFUNCTION(BlueprintCallable, Reliable, Server)
		void UseItem_Server(TSubclassOf<class AItemBase> ItemClass);

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
		void UseItem_NMC(TSubclassOf<class AItemBase> ItemClass);

	void DestroyItem();

private:
	TWeakObjectPtr<ACharacter> Owner;
private:
	TWeakObjectPtr<class AItemBase> Item;


};
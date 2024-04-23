#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Buffs/BuffInstance.h"
#include "BuffComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUSH_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBuffComponent();
protected:
	virtual void BeginPlay() override;

public:
	void AddBuff(TSubclassOf<ABuffInstance> BuffClass);

	void RemoveBuff(ABuffInstance* removeBuff);

	UFUNCTION(BlueprintCallable)
		int GetBuffCount() { return Buffs.Num(); }

	UFUNCTION(Server, Reliable)
		void AddBuff_Server(TSubclassOf<ABuffInstance> BuffClass);
	UFUNCTION(NetMulticast, Reliable)
		void AddBuff_NMC(TSubclassOf<ABuffInstance> BuffClass);
public:
	TWeakObjectPtr<ACharacter> Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,        
	meta = (AllowPrivateAccess))
		TArray<ABuffInstance*> Buffs;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UWDG_BuffBoard> WidgetClass;
	UWDG_BuffBoard* Widget;

	int BuffCount = 0;

};


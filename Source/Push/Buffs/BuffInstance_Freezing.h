#pragma once

#include "CoreMinimal.h"
#include "Buffs/BuffInstance.h"
#include "BuffInstance_Freezing.generated.h"

UCLASS()
class PUSH_API ABuffInstance_Freezing : public ABuffInstance
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void OnEffect() override;
	virtual void OffEffect() override;

	UFUNCTION(Reliable, Server)
		void FreezeON_Server();
	UFUNCTION(NetMulticast, Reliable)
		void FreezeON_NMC();

	UFUNCTION(Reliable, Server)
		void FreezeOFF_Server();
	UFUNCTION(NetMulticast, Reliable)
		void FreezeOFF_NMC();


};

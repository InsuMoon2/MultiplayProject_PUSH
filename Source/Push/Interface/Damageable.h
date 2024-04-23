#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Misc/Structures.h"
#include "Damageable.generated.h"

UINTERFACE(MinimalAPI)
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

class PUSH_API IDamageable
{
	GENERATED_BODY()

public:
	virtual void Hit(AActor* InAttacker, const FHitData& InHitData) = 0;
};

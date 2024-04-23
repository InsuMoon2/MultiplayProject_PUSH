#pragma once

#include "CoreMinimal.h"
#include "Enums.generated.h"

UENUM(BlueprintType)
enum class EDebuff : uint8
{
	ED_None, ED_Root, ED_Freeze, ED_Bleed
};

UENUM(BlueprintType)
enum class ESpeedType : uint8
{
	ES_Walk = 0, ES_Run, ES_Sprint, MAX
};

UENUM(BlueprintType)
enum class EStateType : uint8
{
	ES_Idle = 0, ES_Hitted, ES_Action, ES_Dead, MAX
};

UCLASS()
class PUSH_API UEnums : public UObject
{
	GENERATED_BODY()

};


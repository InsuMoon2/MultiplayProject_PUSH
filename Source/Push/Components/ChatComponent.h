#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ChatComponent.generated.h"


UCLASS(Blueprintable)
class PUSH_API UChatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UChatComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

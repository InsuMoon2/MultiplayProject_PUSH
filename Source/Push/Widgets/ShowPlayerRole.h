// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShowPlayerRole.generated.h"

/**
 * 
 */
UCLASS()
class PUSH_API UShowPlayerRole : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* DisplayRole;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* DisplayServer;

public:
	void SetDisplayText(FString InRole, FString InServer);

	UFUNCTION(BlueprintCallable)
		void ShowPlayerNetRole(APawn* InPawn);
	
};

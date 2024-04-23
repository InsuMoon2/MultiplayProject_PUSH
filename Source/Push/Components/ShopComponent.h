#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShopComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUSH_API UShopComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UShopComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	ACharacter* Owner;
	class APushPlayerController* PlayerController;
	class AMainHUD* MainHUD;

	bool bOpen = false;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillDatas")
		TArray<TSubclassOf<class USkillData>> SkillDatas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDatas")
		TArray<TSubclassOf<class AItemBase>> ItemDatas;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BoughtSkills")
		TArray<TSubclassOf<class USkillData>> BoughtSkills;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BoughtItems")
		TArray<TSubclassOf<class AItemBase>> BoughtItems;

	UPROPERTY(BlueprintReadWrite)
		class USkillSlots* SkillSlots;

	UPROPERTY(BlueprintReadWrite)
		class USkillSlots* ItemSlots;

	UPROPERTY(BlueprintReadWrite)
		class UInventory* Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UMainUI* MainUI;

public:
	UFUNCTION(BlueprintCallable)
		void OpenStoreUI();
};

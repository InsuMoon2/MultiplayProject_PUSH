#include "Items/Item_DotItem.h"
#include "Components/BuffComponent.h"
#include "Global.h"

void AItem_DotItem::BeginPlay()
{
	Super::BeginPlay();

}

void AItem_DotItem::UseItem_Implementation()
{
	Super::UseItem_Implementation();
	if (Owner == nullptr)
		return;

	FVector start = Owner->GetActorLocation();
	FVector end = start + Owner->GetActorForwardVector() * 400.0f;
	TArray<AActor*> ignore;
	ignore.Add(Owner.Get());
	FHitResult result;
	UKismetSystemLibrary::LineTraceSingle(Owner->GetWorld(), start, end, TraceType, false, ignore, DrawType, result, true);

	if (!result.bBlockingHit)
		return;

	APlayerController* controller = Cast<APlayerController>(Owner->GetController());

	ACharacter* character = Cast<ACharacter>(result.Actor);
	if (!character)
		return;
	UBuffComponent* buffComponent = Helpers::GetComponent<UBuffComponent>(character);

	if (!buffComponent)
		return;

	buffComponent->AddBuff(BuffClass);
}

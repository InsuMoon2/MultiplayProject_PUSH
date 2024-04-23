#include "Character/AnimInstance_PushCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/MoveComponent.h"
#include "Global.h"
#include "PushCharacter.h"

void UAnimInstance_PushCharacter::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<APushCharacter>(TryGetPawnOwner());

	if (!OwnerCharacter) return;

	Movement = Helpers::GetComponent<UMoveComponent>(OwnerCharacter);
}

void UAnimInstance_PushCharacter::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!OwnerCharacter) return;

	Speed = OwnerCharacter->GetVelocity().Size2D();
	Falling = OwnerCharacter->GetCharacterMovement()->IsFalling();
	bUseControlYaw = OwnerCharacter->bUseControllerRotationYaw;

	FRotator rotator = OwnerCharacter->GetVelocity().ToOrientationRotator();
	FRotator rotator2 = OwnerCharacter->GetControlRotation();
	FRotator delta = UKismetMathLibrary::NormalizedDeltaRotator(rotator, rotator2);
	PrevRotation = UKismetMathLibrary::RInterpTo(PrevRotation, delta, DeltaSeconds, 25);
	Direction = PrevRotation.Yaw;

	//Pitch = UKismetMathLibrary::FInterpTo(Pitch, OwnerCharacter->GetBaseAimRotation().Pitch, DeltaSeconds, 25);

	Pitch = OwnerCharacter->GetBaseAimRotation().Pitch;
	if (Pitch > 90.0f)
	{
		FVector2D InRange(270.0f, 360.0f);
		FVector2D OutRange(-90.0f, 0.0f);

		Pitch = FMath::GetMappedRangeValueClamped(InRange, OutRange, Pitch);
	}

	//FString Message = FString::Printf(TEXT("%s : , %f"), *OwnerCharacter->CustomPlayerName, Pitch);
	//CLog::Print(Message);
}
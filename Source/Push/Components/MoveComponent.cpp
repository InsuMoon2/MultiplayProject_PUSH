#include "MoveComponent.h"

#include "StateComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Global.h"
#include "GameFramework/CharacterMovementComponent.h"

UMoveComponent::UMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	
}

void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<ACharacter>(GetOwner());

	//2023.12.29 이현중
	//view허용값 설정
	APlayerController* playerController = Cast<APlayerController>(Owner->GetController());

	if (!playerController)
	{
		return;
	}

	playerController->PlayerCameraManager->ViewPitchMax = ViewMaxPitch;
	playerController->PlayerCameraManager->ViewPitchMin = ViewMinPitch;

	UpdateSpeed_Server();
}

void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMoveComponent::OnMoveForward(float InAxis)
{
	if (bCanMove == false)
		return;

	if (!IsValid(Owner.Get()))
		return;
	//FVector direction = UKismetMathLibrary::GetForwardVector(FRotator(0, Owner->GetControlRotation().Yaw, 0));
	FRotator rotator = FRotator(0, Owner->GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();

	//2023.12.28 이현중
	// 앞,뒤 이동
	Owner->AddMovementInput(direction, InAxis);
}

void UMoveComponent::OnMoveRight(float InAxis)
{
	if (bCanMove == false || !Owner.IsValid())
		return;

	//2023.12.28 이현중
	// 좌,우 이동
	//FVector direction = UKismetMathLibrary::GetRightVector(FRotator(0, Owner->GetControlRotation().Yaw, 0));
	FRotator rotator = FRotator(0, Owner->GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	Owner->AddMovementInput(direction, InAxis);

}

//2023.12.29 이현중
// OnTurnAt, OnLookUp 마우스에 따른 시점 이동
void UMoveComponent::OnTurnAt(float Rate)
{
	if (bCanMove == false || !Owner.IsValid())
		return;

	Owner->AddControllerYawInput(Rate * MouseSenceX * GetWorld()->GetDeltaSeconds());
}

void UMoveComponent::OnLookUp(float Rate)
{
	if (bCanMove == false || !Owner.IsValid())
		return;
	Owner->AddControllerPitchInput(Rate * MouseSenceY * GetWorld()->GetDeltaSeconds());
}

void UMoveComponent::SetSpeedPercent_NMC_Implementation(float speed)
{
	SpeedPercent = speed;
}

void UMoveComponent::SetSpeedPercent_Server_Implementation(float speed)
{
	SetSpeedPercent_NMC(speed);
}

void UMoveComponent::UpdateSpeed_NMC_Implementation()
{
	if (!Owner.IsValid())
		return;

	UCharacterMovementComponent* movementComponent = Helpers::GetComponent<UCharacterMovementComponent>(Owner.Get());

	if (!movementComponent)
		return;
	movementComponent->MaxWalkSpeed = Speed * (SpeedPercent / 100);
}

void UMoveComponent::UpdateSpeed_Server_Implementation()
{
	UpdateSpeed_NMC();
}



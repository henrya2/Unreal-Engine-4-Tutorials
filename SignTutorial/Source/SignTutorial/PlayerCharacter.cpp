

#include "SignTutorial.h"
#include "PlayerCharacter.h"

#include "Sign.h"


APlayerCharacter::APlayerCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Action Mappings
	InputComponent->BindAction("Use", EInputEvent::IE_Pressed, this, &APlayerCharacter::Use);

	// Axis Mappings
	InputComponent->BindAxis("MoveFrontBack", this, &APlayerCharacter::MoveFrontBack);
	InputComponent->BindAxis("MoveLeftRight", this, &APlayerCharacter::MoveLeftRight);
	InputComponent->BindAxis("LookUpDown", this, &APlayerCharacter::AddControllerPitchInput);
	InputComponent->BindAxis("LookLeftRight", this, &APlayerCharacter::AddControllerYawInput);
}

void APlayerCharacter::MoveFrontBack(float Value)
{
	if (Controller && Value != 0.0f)
	{
		FRotator Rotation = GetActorRotation();

		if (CharacterMovement->IsMovingOnGround() || CharacterMovement->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}

		FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveLeftRight(float Value)
{
	if (Controller && Value != 0.0f)
	{
		FRotator Rotation = GetActorRotation();

		FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::Use()
{
	FHitResult HitResult(EForceInit::ForceInit);

	bool bTraceSuccess = TraceFromSelf(HitResult, 150.0f, ECollisionChannel::ECC_EngineTraceChannel1);
	if (bTraceSuccess)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			ASign* SignActor = Cast<class ASign>(HitActor);
			if (SignActor)
			{
				// Take the message from the sign
				FString SignMessage = SignActor->GetMessage();

				// Display as debug message
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, SignMessage);
			}
		}
	}
}

bool APlayerCharacter::TraceFromSelf(FHitResult& OutResult, float TraceDistance, ECollisionChannel CollisionChannel)
{
	if (Controller)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		Controller->GetPlayerViewPoint(CameraLocation, CameraRotation);

		FVector StartTrace = CameraLocation;
		FVector ShootDirection = CameraRotation.Vector();
		FVector EndTrace = StartTrace + ShootDirection * TraceDistance;

		FCollisionQueryParams TraceParams(FName(TEXT("TraceFromSelf")), true, this);

		bool bHitReturned = false;
		UWorld* World = GetWorld();
		if (World)
		{
			bHitReturned = World->LineTraceSingle(OutResult, StartTrace, EndTrace, CollisionChannel, TraceParams);
		}

		return bHitReturned;
	}

	return false;
}




#pragma once

#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SIGNTUTORIAL_API APlayerCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

	
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent);

	void MoveFrontBack(float Value);
	void MoveLeftRight(float Value);

	void Use();

	bool TraceFromSelf(FHitResult& OutResult, float TraceDistance, ECollisionChannel CollisionChannel);
};



#pragma once

#include "GameFramework/Actor.h"
#include "Sign.generated.h"

/**
 * 
 */
UCLASS()
class SIGNTUTORIAL_API ASign : public AActor
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = Accessors)
	FString GetMessage() const;
	
	UFUNCTION(BlueprintCallable, Category = Modifiers)
	void SetMessage(const FString& NewMessage);

protected:
	UPROPERTY(EditAnywhere, Category = Messages)
	FString Message;
};

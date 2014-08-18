

#include "SignTutorial.h"
#include "SignTutorialGameMode.h"

#include "PlayerCharacter.h"

ASignTutorialGameMode::ASignTutorialGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
}



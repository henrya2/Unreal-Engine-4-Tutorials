

#include "SignTutorial.h"
#include "Sign.h"


ASign::ASign(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

FString ASign::GetMessage() const
{
	return Message;
}

void ASign::SetMessage(const FString& NewMessage)
{
	Message = NewMessage;
}



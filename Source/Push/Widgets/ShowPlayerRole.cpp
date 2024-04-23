#include "Widgets/ShowPlayerRole.h"
#include "Components/TextBlock.h"

void UShowPlayerRole::SetDisplayText(FString InRole, FString InServer)
{
	if (DisplayRole)
	{
        DisplayRole->SetText(FText::FromString(InRole));
	}

    if (DisplayServer)
    {
        DisplayServer->SetText(FText::FromString(InServer));
    }
}

void UShowPlayerRole::ShowPlayerNetRole(APawn* InPawn)
{
    ENetRole LocalRole = InPawn->GetLocalRole();
    FString Role;

    switch (LocalRole)
    {
    case ENetRole::ROLE_Authority:
        Role = FString("Authority");
        break;

    case ENetRole::ROLE_AutonomousProxy:
        Role = FString("AutonomousProxy");
        break;

    case ENetRole::ROLE_SimulatedProxy:
        Role = FString("SimulatedProxy");
        break;

    case ENetRole::ROLE_None:
        Role = FString("None");
        break;
    }


    FString LocalServer;
    if (InPawn->GetWorld()->IsServer())
    {
        LocalServer = "Running on Server";
    }
    else
    {
        LocalServer = "Running on Client";
    }

    FString LocalRoleString = FString::Printf(TEXT("Role : %s"), *Role);
    FString LocalServerString = FString::Printf(TEXT("Server : %s"), *LocalServer);

    SetDisplayText(LocalRoleString, LocalServerString);
}

#include "PossessLib.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Util/Core/LogUtilLib.h"

bool UPossessLib::TryPossess(AController* Controller, APawn* Pawn, const FPossessProps& Props, EMyPossessFlags Flags)
{
	if( PossessConditionsValid(Controller, Pawn, Props, Flags) )
	{
		DoRePossess(Controller, Pawn, Props.Do, Flags);
		return true;
	}

	return false;
}

bool UPossessLib::PossessConditionsValid(AController* Controller, APawn* Pawn, const FPossessProps& Props, EMyPossessFlags Flags)
{
	if(Pawn == nullptr)
	{
		M_LOG_ERROR(TEXT("Nullptr pawn is passed"));
		return false;
	}

	if(Controller == nullptr)
	{
		M_LOG_ERROR(TEXT("Nullptr controller is passed"));
		return false;
	}

	if(Controller->GetPawn() == nullptr)
	{
		M_LOG_ERROR(TEXT("GetPawn() returned nullptr for controller"));
		return false;
	}
	
	// Checking whether already controlled by another controller if necessary
	if((Flags & EMyPossessFlags::PossessEverIfAlreadyControlled) == EMyPossessFlags::None)
	{
		if(AController* OtherController = Pawn->GetController())
		{
			M_LOG_ERROR(TEXT("Target pawn \"%s\" of class \"%s\" is already possessed by controller \"%s\" of class \"%s\""), *Pawn->GetName(), *Pawn->GetClass()->GetName(), *OtherController->GetName(), *OtherController->GetClass()->GetName());

			PlayPossessErrorSound_IfNecessary(Controller, Props.Do, Flags);
			return false;
		}
	}

	// Checking distance to pawn
	{
		float const DistanceToTargetPawn = Controller->GetPawn()->GetDistanceTo(Pawn);
		float const MaxAllowedDistance = Props.Condition.MaxDistance;
		if(MaxAllowedDistance < DistanceToTargetPawn)
		{
			M_LOG_ERROR(TEXT("Target pawn is too far to possess it (Distance = %f; Maximum allowed distance = %f)"), DistanceToTargetPawn, MaxAllowedDistance);
			return false;
		}
	}

	return true;
}

void UPossessLib::DoRePossess(AController* Controller, APawn* Pawn, const FDoPossessProps& Props, EMyPossessFlags Flags)
{
	checkf(Controller, TEXT("Passed controller must be non-NULL pointer when calling \"%s\""), TEXT(__FUNCTION__));
	checkf(Pawn, TEXT("Passed pawn must be non-NULL pointer when calling \"%s\""), TEXT(__FUNCTION__));

	PlayPossessSound_IfNecessary(Controller, Props, Flags);

	Controller->Possess(Pawn);
}

void UPossessLib::PlayPossessErrorSound_IfNecessary(AController* Controller, const FDoPossessProps& Props, EMyPossessFlags Flags) 
{
	if((Flags & EMyPossessFlags::GameplayFeedback) != EMyPossessFlags::None)
	{
		PlayPossessErrorSound(Controller, Props);
	}
}

void UPossessLib::PlayPossessSound_IfNecessary(AController* Controller, const FDoPossessProps& Props, EMyPossessFlags Flags)
{
	if((Flags & EMyPossessFlags::GameplayFeedback) != EMyPossessFlags::None)
	{
		PlayPossessSound(Controller, Props);
	}
}

void UPossessLib::PlayPossessErrorSound(AController* Controller, const FDoPossessProps& Props) 
{
	if(USoundBase* Sound = Props.Sounds.PossessError)
	{
		UGameplayStatics::PlaySound2D(Controller, Sound);
	}
}

void UPossessLib::PlayPossessSound(AController* Controller, const FDoPossessProps& Props)
{
	if(USoundBase* Sound = Props.Sounds.Possessed)
	{
		UGameplayStatics::PlaySoundAtLocation(Controller, Sound, Controller->GetPawn()->GetActorLocation(), Controller->GetPawn()->GetActorRotation());
	}
}

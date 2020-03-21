#include "PossessControllerComponent.h"
#include "PossessLib.h"
#include "Util/Core/LogUtilLib.h"

#include "GameFramework/Controller.h"
#include "Engine/World.h"


UPossessControllerComponent::UPossessControllerComponent()
{
	bEditableWhenInherited = true;
}

UPossessControllerComponent* UPossessControllerComponent::CreateInitializedDefaultSubobject(AController* OwnerController, FName InName)
{
	checkf(OwnerController, TEXT("When calling %s passed owner controller must be valid NON-null pointer"), TEXT(__FUNCTION__));
	UPossessControllerComponent* Obj = OwnerController->CreateDefaultSubobject<UPossessControllerComponent>(InName);
	return Obj;
}

UPossessControllerComponent* UPossessControllerComponent::NewInitializedPossessControllerComponent(AController* OwnerController, FName InName)
{
	checkf(OwnerController, TEXT("When calling %s passed owner controller must be valid NON-null pointer"), TEXT(__FUNCTION__));
	UPossessControllerComponent* Obj = NewObject<UPossessControllerComponent>(OwnerController, UPossessControllerComponent::StaticClass());
	return Obj;
}

bool UPossessControllerComponent::TryPossessActor(AActor* Actor, EMyPossessFlags Flags)
{	
	if( MayPossessActor(Actor, Flags) )
	{
		DoRePossess(Cast<APawn>(Actor), Flags);
		return true;
	}

	return false;
}

bool UPossessControllerComponent::MayPossessActor(AActor* Actor, EMyPossessFlags Flags)
{
	const TCHAR* ErrorMessage = nullptr;

	#ifdef WITH_EDITOR
	if( ! GetWorld()->IsGameWorld() )
	{
		ErrorMessage = TEXT("Unable to possess - editor world");
	}
	#endif // WITH_EDITOR

	M_LOG(TEXT("Checking whether controller \"%s\" of class \"%s\" may possess an actor"), *GetOwnerController()->GetName(), *GetOwnerController()->GetClass()->GetName());
	M_LOG(TEXT("Owner is object \"%s\" of class \"%s\""), *GetOwner()->GetName(), *GetOwner()->GetClass()->GetName());

	bool bNecessaryGameplayFeedbackAlreadyDone = false;
	if(Actor == nullptr)
	{
		ErrorMessage = TEXT("Unable to possess: nullptr passed for actor");
	}
	else
	{
		checkf(Actor, TEXT("At this point the actor pointer must be NON-null pointer"));
		M_LOG(TEXT("Target actor is \"%s\" of class \"%s\""), *AActor::GetDebugName(Actor), *Actor->GetClass()->GetName());
		if( ! IsValid(Actor) )
		{
			ErrorMessage = TEXT("IsValid returned false for target actor");
		}
		else
		{
			if( auto TargetPawn = Cast<APawn>(Actor) )
			{
				if( ! MayPossessPawn(TargetPawn, Flags))
				{
					ErrorMessage = TEXT("Invalid possess conditions");
					// Necessary gameplay feedback was already processed by the PossessConditionsValid
					bNecessaryGameplayFeedbackAlreadyDone = true;
				}
			}
			else
			{
				ErrorMessage = TEXT("target actor is not a pawn");
			}
		}
	}


	if(ErrorMessage)
	{
		M_LOG_ERROR(TEXT("Unable to possess the pawn: %s"), ErrorMessage);
		if( ! bNecessaryGameplayFeedbackAlreadyDone )
		{
			UPossessLib::PlayPossessErrorSound_IfNecessary(GetOwnerController(), PossessProps.Do, Flags);
		}
		return false;
	}
	return true;

}

bool UPossessControllerComponent::TryPossess(APawn* Pawn, EMyPossessFlags Flags)
{
	if(MayPossessPawn(Pawn, Flags))
	{
		DoRePossess(Pawn, Flags);
		return true;
	}
	return false;
}

void UPossessControllerComponent::DoRePossess_Implementation(APawn* Pawn, EMyPossessFlags Flags)
{
	M_LOG_ERROR(TEXT("Possession on controller \"%s\" of class \"%s\""), *GetOwnerController()->GetName(), *GetOwnerController()->GetClass()->GetName());
	UPossessLib::DoRePossess(GetOwnerController(), Pawn, PossessProps.Do, Flags);
}

bool UPossessControllerComponent::MayPossessPawn_Implementation(APawn* Pawn, EMyPossessFlags Flags) const
{
	return UPossessLib::PossessConditionsValid(GetOwnerController(), Pawn, PossessProps, Flags);
}

AController* UPossessControllerComponent::GetOwnerController() const
{
	return CastChecked<AController>(GetOwner(), ECastCheckedType::NullChecked);
}

APawn* UPossessControllerComponent::GetPawn() const
{
	return GetOwnerController()->GetPawn();
}

void UPossessControllerComponent::SetMainPawn(APawn* NewPawn)
{
	MainPawn = NewPawn;
}

bool UPossessControllerComponent::TryTogglePossess(AActor* TargetPawnActor, EMyPossessFlags Flags)
{
	M_LOG(TEXT("Toggling the pawn"));
	if(GetMainPawn())
	{
		M_LOG(TEXT("Main pawn \"%s\" of class \"%s\""), *GetMainPawn()->GetName(), *GetMainPawn()->GetClass()->GetName());
	}
	else
	{
		M_LOG(TEXT("Main pawn is nullptr"));
	}
	if(GetPawn())
	{
		M_LOG(TEXT("GetPawn() returns \"%s\" of class \"%s\""), *GetPawn()->GetName(), *GetPawn()->GetClass()->GetName());
	}
	else
	{
		M_LOG(TEXT("GetPawn() returns nullptr"));
	}
	if(TargetPawnActor)
	{
		M_LOG(TEXT("Target actor \"%s\" of class \"%s\""), *TargetPawnActor->GetName(), *TargetPawnActor->GetClass()->GetName());
	}
	if(GetMainPawn() == GetPawn())
	{
		M_LOG(TEXT("We're controlling main pawn - trying to possess the new pawn"));
		return TryPossessActor(TargetPawnActor, Flags);
	}
	else
	{
		M_LOG(TEXT("We're controlling secondary pawn - trying to return to the main pawn"));
		PossessMainPawn(Flags);
		return true;
	}
}

void UPossessControllerComponent::PossessMainPawn(EMyPossessFlags Flags)
{
	PawnStack.Empty();
	if(APawn* NewPawn = GetMainPawn())
	{
		DoRePossess(NewPawn, Flags);
	}
}

void UPossessControllerComponent::OnController_Possessed(APawn* const Pawn)
{
	#ifdef WITH_EDITOR
	if( ! GetWorld()->IsGameWorld() )
	{
		return;
	}
	#endif WITH_EDITOR

	if(Pawn != nullptr)
	{
		if(MainPawn == nullptr)
		{
			MainPawn = Pawn;
		}
		if(PawnStack.Num() == 0 || PawnStack.Last() != Pawn)
		{
			PawnStack.Add(Pawn);
		}
	}
}

void UPossessControllerComponent::OnController_UnPossessed(APawn* OldPawn)
{
	#ifdef WITH_EDITOR
	if( ! GetWorld()->IsGameWorld() )
	{
		return;
	}
	#endif // WITH_EDITOR

	// Warning old pawn DO may be unstacked (as the stacked may be cleared!)
	if(PawnStack.Num() > 0 && PawnStack.Last() != OldPawn)
	{
		PawnStack.Pop();
	}
}

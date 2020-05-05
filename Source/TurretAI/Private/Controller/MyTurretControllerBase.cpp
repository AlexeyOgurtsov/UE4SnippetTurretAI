#include "MyTurretControllerBase.h"
#include "Turret\I\ITurret.h"
#include "Turret\I\TurretLib.h"
#include "Util\Core\LogUtilLib.h"

/**
* TODO: Store
* 	Last seen enemy time
* 	Last battle action time
*
* TODO: Provide blackboard key: last seen enemy etc.
*/

AMyTurretControllerBase::AMyTurretControllerBase()
{
}

void AMyTurretControllerBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMyTurretControllerBase::OnPossess(APawn* const InPawn)
{
	Super::OnPossess(InPawn);
	if(InPawn)
	{
		PrefixString = FString::Printf(TEXT("Ai ctrl on act \"%s\" (ctrl cls=\"%s\")"), *InPawn->GetName(), *GetClass()->GetName());

		M_LOG(TEXT("New pawn is possessed"));
		if(TScriptInterface<ITurret> TurretPawn = InPawn)
		{
			BindToEvents(TurretPawn);
		}

		if(BehavTree)
		{
			RunBehaviorTree(BehavTree);
		}
		else
		{
			M_LOG_WARN(TEXT("No behavior tree is set, skipping running behavior tree"));
		}
	}
}

void AMyTurretControllerBase::OnUnPossess()
{
	if(TScriptInterface<ITurret> TurretPawn = GetPawn())
	{
		UnbindFromEvents(TurretPawn);
	}
	Super::OnUnPossess();
}

void AMyTurretControllerBase::OnSeePawn_Implementation(APawn* const InPawn)
{
	Super::OnSeePawn_Implementation(InPawn);
}

void AMyTurretControllerBase::OnDamageStateChanged_Implementation()
{
	Super::OnDamageStateChanged_Implementation();
}

void AMyTurretControllerBase::OnAimingFinished_Implementation(const FOnTurretAimingFinishedDelegateArgs& InArgs)
{
	M_LOG(TEXT("%s: %s"), *PrefixString, TEXT(__FUNCTION__));
}

void AMyTurretControllerBase::BindToEvents_Implementation(const TScriptInterface<ITurret>& InTurret)
{
	InTurret->GetTurretEvents()->OnAimingFinished.AddDynamic(this, &AMyTurretControllerBase::OnAimingFinished);
}

void AMyTurretControllerBase::UnbindFromEvents_Implementation(const TScriptInterface<ITurret>& InTurret)
{
	InTurret->GetTurretEvents()->OnAimingFinished.RemoveAll(this);
}

TScriptInterface<ITurret> AMyTurretControllerBase::GetTurret() const
{
	return TScriptInterface<ITurret>(GetPawn());
}

TScriptInterface<ITurret> AMyTurretControllerBase::GetTurretChecked() const
{
	const TScriptInterface<ITurret> Turret = GetTurret();
	checkf(Turret, TEXT("ITurret interface must be supported when calling \"%s\""), TEXT(__FUNCTION__));
	return Turret;
}

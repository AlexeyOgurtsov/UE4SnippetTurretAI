#include "MyPlayerController.h"
#include "MyPlayerPawn.h"
#include "MyGameConfig.h"
#include "GameUtil/MyTargetActor.h"
#include "Turret/I/ITurret.h"
#include "Turret/I/TurretEvents.h"
#include "GameUtil/Possess/PossessControllerComponent.h"

#include "Util/Core/LogUtilLib.h"

MyPCType::AMyPlayerController()
{
	PossessComponent = UPossessControllerComponent::CreateInitializedDefaultSubobject(this, TEXT("PossessComponent"));
	AddSelectableActorClass(AMyTargetActor::StaticClass());
}

void MyPCType::OnUnPossess()
{
	if(PossessComponent)
	{
		PossessComponent->OnController_UnPossessed(GetPawn());
	}
	if (ITurret* Tur = Cast<ITurret>(GetPawn()))
	{
		OnUnPossessTurret(Tur);
	}
	Super::OnUnPossess();
}

void MyPCType::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(PossessComponent)
	{
		PossessComponent->OnController_Possessed(InPawn);
	}
	if (ITurret* Tur = Cast<ITurret>(GetPawn()))
	{
		OnPossessTurret(Tur);
	}
}

void MyPCType::OnUnPossessTurret(ITurret* const Turret)
{
	// @TODO: ubind events
	Turret->GetTurretEvents()->OnAimingFinished.RemoveAll(this);
}

void MyPCType::OnPossessTurret(ITurret* const Turret)
{
	if (Turret)
	{
		Turret->GetTurretEvents()->OnAimingFinished.AddDynamic(this, &MyPCType::OnAimFinished);
	}
}

void MyPCType::OnAimFinished(const FOnTurretAimingFinishedDelegateArgs& InAimingFinished)
{
	AActor* const TargetActor = InAimingFinished.TargetActor;
	// @TODO: Log aiming result
	FString TargetActorName;
	FString TargetActorClassName;
	if (TargetActor)
	{
		TargetActorName = *TargetActor->GetName();
		TargetActorClassName = *TargetActor->GetClass()->GetName();
	}
	else
	{
		TargetActorName = FString(TEXT("nullptr"));
		TargetActorClassName = FString(TEXT("nullptr"));
	}

	M_LOG(TEXT("%s: TargetActor is \"%s\""), TEXT(__FUNCTION__), *TargetActorName, *TargetActorClassName);
}
 
void MyPCType::BeginPlay()
{
	M_LOGFUNC();

	Super::BeginPlay();
}

void MyPCType::Axis_LookPitch(APawn* P, float InAmount)
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Axis_LookPitch(P, InAmount);
}

void MyPCType::Axis_LookYaw(APawn* P, float InAmount)
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Axis_LookYaw(P, InAmount);
}

void MyPCType::Axis_Forward(APawn* P, float InAmount)
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Axis_Forward(P, InAmount);
}

void MyPCType::Axis_Right(APawn* P, float InAmount)
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Axis_Right(P, InAmount);
}

void MyPCType::Axis_Up(APawn* P, float InAmount)
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Axis_Up(P, InAmount);
}

void MyPCType::Action_Use()
{
	AActor* const TargetActor = TraceByLook();
	PossessComponent->TryTogglePossess(TargetActor);
}

void MyPCType::Action_UseTwo()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_UseTwo();
}

void MyPCType::Action_UseThree()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_UseThree();
}

void MyPCType::Action_Fire()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_Fire();
}

void MyPCType::Action_FireTwo()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_FireTwo();
}

void MyPCType::Action_FireThree()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_FireThree();
}

void MyPCType::Action_SelectZero()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_SelectZero();
}

void MyPCType::Action_SelectOne()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_SelectOne();
}

void MyPCType::Action_SelectTwo()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_SelectTwo();
}

void MyPCType::Action_SelectThree()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_SelectThree();
}

void MyPCType::Action_SelectFour()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_SelectFour();
}

void MyPCType::Action_SelectFive()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_SelectFive();
}

void MyPCType::Action_SelectSix()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_SelectSix();
}

void MyPCType::Action_SelectSeven()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_SelectSeven();
}

void MyPCType::Action_SelectEight()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_SelectEight();
}

void MyPCType::Action_SelectNine()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_SelectNine();
}

void MyPCType::Action_OpenGameMenu()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_OpenGameMenu();
}

void MyPCType::Action_CloseGameMenu()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_CloseGameMenu();
}

void MyPCType::Action_DebugOne()
{	
	if (auto P = Cast<ITUPawnActions>(GetPawn()))
	{
		ITUPawnActions::Execute_OnController_Action_DebugOne(GetPawn());
	}
	else
	{
		M_LOG_ERROR(TEXT("No pawn or it does now support ITUPawnActions interface"));
	}
}

void MyPCType::Action_DebugTwo()
{
	if (auto P = Cast<ITUPawnActions>(GetPawn()))
	{
		ITUPawnActions::Execute_OnController_Action_DebugTwo(GetPawn());
	}
	else
	{
		M_LOG_ERROR(TEXT("No pawn or it does now support ITUPawnActions interface"));
	}
}

void MyPCType::Action_DebugThree()
{
	if (auto P = Cast<ITUPawnActions>(GetPawn()))
	{
		ITUPawnActions::Execute_OnController_Action_DebugThree(GetPawn());
	}
	else
	{
		M_LOG_ERROR(TEXT("No pawn or it does now support ITUPawnActions interface"));
	}
}

MyPawnType* MyPCType::GetMyPawn() const
{
	return Cast<MyPawnType>(GetPawn());
}

MyPawnType* MyPCType::GetMyPawnLogged(ELogFlags InLogFlags) const
{
	MyPawnType* const P = GetMyPawn();
	if(P == nullptr)
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GetMyPawn() returned NULL"));
	}
	return P;
}

MyPawnType* MyPCType::GetMyPawnChecked() const
{
	MyPawnType* const P = GetMyPawn();
	checkf(P, TEXT("GetMyPawn must return non-NULL pawn!"));
	return P;
}


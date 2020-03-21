#include "MyPlayerPawn.h"
#include "MyPlayerController.h"
#include "MyGameConfig.h"

#include "Util/Core/LogUtilLib.h"

#include "GameFramework/FloatingPawnMovement.h"

#include "PawnBase/MyPawnImpl.h"

/**
* TODO Fix: Movement
* 1. Floating pawn movement: does it work by default (seems like not)?
*/

namespace
{
	namespace Config
	{
		constexpr float MAX_SPEED = 100.0F;
		constexpr float ACCELERATION = 0.0F;
		constexpr float DECELERATION = 0.0F;
	} // Config
} // anonymous

MyPawnType::AMyPlayerPawn()
{
	Impl = UMyPawnImpl::CreateInitialized(this, TEXT("Impl"));
	InitMovement();
}

void MyPawnType::OnController_Axis_LookPitch_Implementation(float InAmount)
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Axis_LookPitch_Implementation(InAmount);
}

void MyPawnType::OnController_Axis_LookYaw_Implementation(float InAmount)
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Axis_LookYaw_Implementation(InAmount);
}

void MyPawnType::OnController_Axis_Forward_Implementation(float InAmount)
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Axis_Forward_Implementation(InAmount);
}

void MyPawnType::OnController_Axis_Right_Implementation(float InAmount)
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Axis_Right_Implementation(InAmount);
}

void MyPawnType::OnController_Axis_Up_Implementation(float InAmount)
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Axis_Up_Implementation(InAmount);
}

void MyPawnType::OnController_Action_Use_Implementation()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Action_Use_Implementation();
}

void MyPawnType::OnController_Action_UseTwo_Implementation()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Action_UseTwo_Implementation();
}

void MyPawnType::OnController_Action_UseThree_Implementation()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Action_UseThree_Implementation();
}

void MyPawnType::PawnStartFire(uint8 FireModeNum)
{
	// FireModeNum is index of the fire mode (see actions Fire, FireTwo, FireThree)
	// HINT Super::PawnStartFire does nothing in the UE4.24 version!
	Super::PawnStartFire(FireModeNum);
	// @TODO: Typically here implement the real firing!
}

void MyPawnType::OnController_Action_Fire_Implementation()
{
	// We process firing inside the PawnStartFire
}

void MyPawnType::OnController_Action_FireTwo_Implementation()
{
	// We process firing inside the PawnStartFire
}

void MyPawnType::OnController_Action_FireThree_Implementation()
{
	// We process firing inside the PawnStartFire
}

void MyPawnType::OnController_Action_SelectZero_Implementation()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Action_SelectZero_Implementation();
}

void MyPawnType::OnController_Action_SelectOne_Implementation()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Action_SelectOne_Implementation();
}

void MyPawnType::OnController_Action_SelectTwo_Implementation()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Action_SelectTwo_Implementation();
}

void MyPawnType::OnController_Action_SelectThree_Implementation()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Action_SelectThree_Implementation();
}

void MyPawnType::OnController_Action_SelectFour_Implementation()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Action_SelectFour_Implementation();
}

void MyPawnType::OnController_Action_SelectFive_Implementation()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Action_SelectFive_Implementation();
}

void MyPawnType::OnController_Action_SelectSix_Implementation()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Action_SelectSix_Implementation();
}

void MyPawnType::OnController_Action_SelectSeven_Implementation()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Action_SelectSeven_Implementation();
}

void MyPawnType::OnController_Action_SelectEight_Implementation()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Action_SelectEight_Implementation();
}

void MyPawnType::OnController_Action_SelectNine_Implementation()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Action_SelectNine_Implementation();
}

void MyPawnType::OnController_Action_OpenGameMenu_Implementation()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Action_OpenGameMenu_Implementation();
}

void MyPawnType::OnController_Action_CloseGameMenu_Implementation()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Action_CloseGameMenu_Implementation();
}

void MyPawnType::OnController_Action_DebugOne_Implementation()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Action_DebugOne_Implementation();
}

void MyPawnType::OnController_Action_DebugTwo_Implementation()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Action_DebugTwo_Implementation();
}

void MyPawnType::OnController_Action_DebugThree_Implementation()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::OnController_Action_DebugThree_Implementation();
}

void MyPawnType::MyBeginPlay_Implementation()
{
	M_LOGFUNC();

	Super::MyBeginPlay_Implementation();
	// Custom actions here
}

void MyPawnType::InitMovement()
{
	M_LOGFUNC();
	UFloatingPawnMovement* const MyMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	MyMovement->Acceleration = Config::ACCELERATION;
	MyMovement->Deceleration = Config::DECELERATION;
	MyMovement->MaxSpeed = Config::MAX_SPEED;
	Movement = MyMovement;
}

MyPCType* MyPawnType::GetMyPC() const
{
	return Cast<MyPCType>(GetController());
}

MyPCType* MyPawnType::GetMyPCLogged(ELogFlags InLogFlags) const
{
	MyPCType* const PC = GetMyPC();
	if(PC == nullptr)
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GetMyPC() returned NULL"));
	}
	return PC;
}

MyPCType* MyPawnType::GetMyPCChecked() const
{
	MyPCType* const PC = GetMyPC();
	checkf(PC, TEXT("GetMyPawn must return non-NULL pawn!"));
	return PC;
}
float AMyPlayerPawn::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float const Result = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return Impl->TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

FMyHitState AMyPlayerPawn::GetHitState_Implementation() const
{
	return Impl->HitState;
}

UMyPawnEvents* AMyPlayerPawn::GetEvents_Implementation() const
{
	return Impl->MyEvents;
}

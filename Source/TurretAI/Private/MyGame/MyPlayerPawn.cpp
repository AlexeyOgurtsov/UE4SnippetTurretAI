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

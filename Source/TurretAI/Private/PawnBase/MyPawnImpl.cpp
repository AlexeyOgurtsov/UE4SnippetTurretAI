#include "MyPawnImpl.h"
#include "PawnBase/MyPawnEvents.h"

#include "Util/Core/LogUtilLib.h"

#include "GameFramework/Actor.h"

UMyPawnImpl::UMyPawnImpl()
{
	MyEvents = CreateDefaultSubobject<UMyPawnEvents>(TEXT("Events"));
}

UMyPawnImpl* UMyPawnImpl::CreateInitialized(AActor* const InOwner, const FName InName, UWeaponComponent* InWeaponComponent)
{
	UMyPawnImpl* const Obj = InOwner->CreateDefaultSubobject<UMyPawnImpl>(InName);
	Obj->Owner = InOwner;
	Obj->WeaponComponent = InWeaponComponent;
	return Obj;
}

float UMyPawnImpl::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	SetNewDamageState(HitState.Hits - DamageAmount);
	return DamageAmount;
}
void UMyPawnImpl::SetNewDamageState(float const InNewDamage, bool const bInNotify)
{
	HitState.Hits = InNewDamage;

	if(bInNotify)
	{
		MyEvents->OnDamageStateChanged.Broadcast();
	}
	
	if(HitState.Hits < 0.0F)
	{
		M_LOG(TEXT("Damage is below zero, destroying"));
		bool const bDestroyed = GetOwner()->Destroy(true, true);
		M_LOG_ERROR_IF( ! bDestroyed, TEXT("Unable to destroy the actor"));
	}
}

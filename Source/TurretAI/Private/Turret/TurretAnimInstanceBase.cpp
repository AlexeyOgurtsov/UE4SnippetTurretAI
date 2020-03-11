#include "TurretAnimInstanceBase.h"
#include "Util/Core/LogUtilLib.h"

#include "Engine/World.h"


// @TODO:
// 1. Update gun in the given direction (clockwise or counter-clockwise)

// @TODO animation questions:
// 1. Whether the UAnimInstanceBase update function is executed on the main thread or on the separate thread?
// 2. Can we create the setter function in the Anim instance ans use it outside the animation blueprint?

void UTurretAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	InitializeLinkToTurret();
}

void UTurretAnimInstanceBase::InitializeLinkToTurret()
{
	if(AActor* TheOwningActor = GetOwningActor())
	{
		Turret = TheOwningActor;
		if( ! Turret )
		{
			M_LOG_ERROR(TEXT("Unable to link to turret: %s interface is NOT supported!"), *UTurret::StaticClass()->GetName());

		}
	}
	else
	{
		if( ! GetWorld()->IsEditorWorld() )
		{
			M_LOG_ERROR(TEXT("Unable to link to turret: Owning actor is nullptr"));
		}
	}
}

void UTurretAnimInstanceBase::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

	if(Turret)
	{
		TurretState = Turret->GetTurretState();
	}

}

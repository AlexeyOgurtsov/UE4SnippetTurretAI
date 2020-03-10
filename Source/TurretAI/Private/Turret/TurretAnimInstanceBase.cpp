#include "TurretAnimInstanceBase.h"
#include "GameUtil/Math/GameMathTypes.h"
#include "Math/UnrealMathUtility.h"


// @TODO:
// 1. Update gun in the given direction (clockwise or counter-clockwise)

// @TODO animation questions:
// 1. Whether the UAnimInstanceBase update function is executed on the main thread or on the separate thread?
// 2. Can we create the setter function in the Anim instance ans use it outside the animation blueprint?

void UTurretAnimInstanceBase::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);
	// Yaw is between (-180; 180], so no special interpolation is necessary.
	CurrentTurretYawInComponentSpace = UGameMath::GetUnwindedDegreesUpdatedToTarget(DeltaTimeX, CurrentTurretYawInComponentSpace, TargetTurretYawInComponentSpace, TurretYawUpdate, TurretYawUpdateDirection);
	// Yaw is between [-90; 90], so no special interpolation is necessary.
	CurrentGunPitchInComponentSpace = UGameMath::GetUnwindedDegreesUpdatedToTarget(DeltaTimeX, CurrentGunPitchInComponentSpace, TargetGunPitchInComponentSpace, GunPitchUpdate, GunPitchUpdateDirection);
}

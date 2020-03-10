#pragma once

#include "Animation/AnimInstance.h"
#include "GameUtil/Math/GameMathTypes.h"
#include "TurretAnimInstanceBase.generated.h"

UCLASS()
class UTurretAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

public:
	/**
	* Target turret yaw degrees in component space.
	*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	float TargetTurretYawInComponentSpace = 0.0F;

	/**
	* Target gun pitch degrees in component space.
	*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	float TargetGunPitchInComponentSpace = 0.0F;

	/**
	* Current turret yaw degrees in component space.
	*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	float CurrentTurretYawInComponentSpace = 0.0F;

	/**
	* Current gun pitch degrees in component space.
	*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	float CurrentGunPitchInComponentSpace = 0.0F;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	ERotationDirection TurretYawUpdateDirection = ERotationDirection::CounterClockwise;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	ERotationDirection GunPitchUpdateDirection = ERotationDirection::CounterClockwise;

	/**
	* Speed of turret yaw update.
	*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	FGameFloatUpdate TurretYawUpdate;

	/**
	* Speed of turret yaw update.
	*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	FGameFloatUpdate GunPitchUpdate;

	// ~UAnimInstance Begin
	void NativeUpdateAnimation(float DeltaTimeX) override;
	// ~UAnimInstance End
	
private:
};

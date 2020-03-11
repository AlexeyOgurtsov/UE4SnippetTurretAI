#pragma once

#include "UObject/Interface.h"
#include "GameUtil/Math/GameMathTypes.h"
#include "ITurret.generated.h"

USTRUCT(BlueprintType)
struct FTurretState 
{
	GENERATED_BODY()

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERotationDirection TurretYawUpdateDirection = ERotationDirection::CounterClockwise;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERotationDirection GunPitchUpdateDirection = ERotationDirection::CounterClockwise;

	/**
	* Speed of turret yaw update.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameFloatUpdate TurretYawUpdate;

	/**
	* Speed of turret yaw update.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameFloatUpdate GunPitchUpdate;
};

UINTERFACE(BlueprintType)
class UTurret : public UInterface
{
	GENERATED_BODY()

public:
};

class ITurret
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta=(DisplayName="GetTurretState"), Category=ITurret)
	FTurretState K2_GetTurretState() const;
	FTurretState GetTurretState() const 
	{
		return Execute_K2_GetTurretState(Cast<UObject>(this));
	}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta=(DisplayName="SetTurretState"), Category=ITurret)
	void K2_SetTurretState(const FTurretState& InState);
	void SetTurretState(const FTurretState& InState)
	{
		Execute_K2_SetTurretState(Cast<UObject>(this), InState);
	}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta=(DisplayName="SetTargetTurretYawInComponentSpace"), Category=ITurret)
	void K2_SetTargetTurretYawInComponentSpace(float NewYawDegs);
	virtual void K2_SetTargetTurretYawInComponentSpace_Implementation(float NewYawDegs)
	{
		FTurretState State = ITurret::Execute_K2_GetTurretState(Cast<UObject>(this));
		State.TargetTurretYawInComponentSpace = NewYawDegs;
		ITurret::Execute_K2_SetTurretState(Cast<UObject>(this), State);
	}
	void SetTargetTurretYawInComponentSpace(float NewYawDegs)
	{
		Execute_K2_SetTargetTurretYawInComponentSpace(Cast<UObject>(this), NewYawDegs);
	}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta=(DisplayName="SetTargetGunPitchInComponentSpace"), Category=ITurret)
	void K2_SetTargetGunPitchInComponentSpace(float NewPitchDegs);
	virtual void K2_SetTargetGunPitchInComponentSpace_Implementation(float NewPitchDegs)
	{
		FTurretState State = ITurret::Execute_K2_GetTurretState(Cast<UObject>(this));
		State.TargetGunPitchInComponentSpace = NewPitchDegs;
		ITurret::Execute_K2_SetTurretState(Cast<UObject>(this), State);
	}
	void SetTargetGunPitchInComponentSpace(float NewPitchDegs)
	{
		Execute_K2_SetTargetGunPitchInComponentSpace(Cast<UObject>(this), NewPitchDegs);
	}
};


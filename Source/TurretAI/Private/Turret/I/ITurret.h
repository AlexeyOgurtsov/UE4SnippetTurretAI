#pragma once

#include "UObject/Interface.h"
#include "GameUtil/Math/GameMathTypes.h"
#include "Util/Core/LogUtilLib.h"
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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta=(DisplayName="SetTurretYawUpdateDirection"), Category=ITurret)
	void K2_SetTurretYawUpdateDirection(ERotationDirection NewDirection);
	virtual void K2_SetTurretYawUpdateDirection_Implementation(ERotationDirection NewDirection)
	{
		FTurretState State = ITurret::Execute_K2_GetTurretState(Cast<UObject>(this));
		State.TurretYawUpdateDirection = NewDirection;
		ITurret::Execute_K2_SetTurretState(Cast<UObject>(this), State);
	}
	void SetTurretYawUpdateDirection(ERotationDirection NewDirection)
	{
		Execute_K2_SetTurretYawUpdateDirection(Cast<UObject>(this), NewDirection);
	}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta=(DisplayName="SetGunPitchUpdateDirection"), Category=ITurret)
	void K2_SetGunPitchUpdateDirection(ERotationDirection NewDirection);
	virtual void K2_SetGunPitchUpdateDirection_Implementation(ERotationDirection NewDirection)
	{
		FTurretState State = ITurret::Execute_K2_GetTurretState(Cast<UObject>(this));
		State.GunPitchUpdateDirection = NewDirection;
		ITurret::Execute_K2_SetTurretState(Cast<UObject>(this), State);
	}
	void SetGunPitchUpdateDirection(ERotationDirection NewDirection)
	{
		Execute_K2_SetGunPitchUpdateDirection(Cast<UObject>(this), NewDirection);
	}

	void AddTargetTurretYawInComponentSpace(float DeltaYawDegs)
	{
		if(DeltaYawDegs != 0.0F)
		{
			FTurretState State = ITurret::Execute_K2_GetTurretState(Cast<UObject>(this));
			const float NewYawDegs = State.CurrentTurretYawInComponentSpace + DeltaYawDegs;
			ITurret::Execute_K2_SetTargetTurretYawInComponentSpace(Cast<UObject>(this), NewYawDegs);
		}
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
	void AddTargetGunPitchInComponentSpace(float DeltaPitchDegs)
	{
		if(DeltaPitchDegs != 0.0F)
		{
			FTurretState State = ITurret::Execute_K2_GetTurretState(Cast<UObject>(this));
			const float NewPitchDegs = State.CurrentGunPitchInComponentSpace + DeltaPitchDegs;
			ITurret::Execute_K2_SetTargetGunPitchInComponentSpace(Cast<UObject>(this), NewPitchDegs);
		}
	}
	void RotateGunPitchMinimal(float DeltaPitchDegs)
	{
		AddTargetGunPitchInComponentSpace(DeltaPitchDegs);
		const ERotationDirection NewDirection = GetMinimalPitchRotateToTargetDirection();
		SetGunPitchUpdateDirection(NewDirection);
	}
	void RotateTurretYawMinimal(float DeltaYawDegs)
	{
		AddTargetTurretYawInComponentSpace(DeltaYawDegs);
		const ERotationDirection NewDirection = GetMinimalYawRotateToTargetDirection();
		SetTurretYawUpdateDirection(NewDirection);
	}
	ERotationDirection GetMinimalYawRotateToTargetDirection() const
	{
		FTurretState State = ITurret::Execute_K2_GetTurretState(Cast<UObject>(this));
		const ERotationDirection NewDirection = ((State.TargetTurretYawInComponentSpace - State.CurrentTurretYawInComponentSpace) < 0) ? ERotationDirection::Clockwise : ERotationDirection::CounterClockwise;
		return NewDirection;
	}
	ERotationDirection GetMinimalPitchRotateToTargetDirection() const
	{
		FTurretState State = ITurret::Execute_K2_GetTurretState(Cast<UObject>(this));
		const ERotationDirection NewDirection = ((State.TargetGunPitchInComponentSpace - State.CurrentGunPitchInComponentSpace) < 0) ? ERotationDirection::Clockwise : ERotationDirection::CounterClockwise;
		return NewDirection;
	}
};


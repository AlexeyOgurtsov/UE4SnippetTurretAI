#pragma once

#include "TurretTypes.h"

#include "UObject/Interface.h"
#include "Util/Core/LogUtilLib.h"
#include "ITurret.generated.h"


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
	// ~Main interface Begin
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta=(DisplayName="GetTurretEvents"), Category=ITurret)
	UTurretEvents* K2_GetTurretEvents() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (DisplayName = "GetTargetAzimuthAndElevation"), Category = ITurret)
	FVector2D K2_GetTargetAzimuthAndElevation(AActor* InTarget) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (DisplayName = "IsTargetReachable"), Category = ITurret)
	bool K2_IsTargetReachable(float InDistance, const FVector2D& InAzimuthAndElevation) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (DisplayName = "IsTargetReachableByElevation"), Category = ITurret)
	bool K2_IsTargetReachableByElevation(const FVector2D& InTargetAndElevation) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (DisplayName = "IsTargetReachableByDistance"), Category = ITurret)
	bool K2_IsTargetReachableByDistance(float InDistance) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (DisplayName = "StartAimingAt"), Category = ITurret)
	ETurretAimingResult K2_StartAimingAt(AActor* NewTargetActor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (DisplayName = "StopAiming"), Category = ITurret)
	void K2_StopAiming(const FString& InReason, ETurretAimingResult InResult);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (DisplayName = "IsAimingFinished"), Category = ITurret)
	bool K2_IsAimingFinished() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (DisplayName = "GetTurretState"), Category = ITurret)
	FTurretState K2_GetTurretState() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (DisplayName = "SetTurretState"), Category = ITurret)
	void K2_SetTurretState(const FTurretState& InState);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (DisplayName = "SetTargetGunPitchInComponentSpace"), Category = ITurret)
	void K2_SetTargetGunPitchInComponentSpace(float NewPitchDegs);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (DisplayName = "SetTargetTurretYawInComponentSpace"), Category = ITurret)
	void K2_SetTargetTurretYawInComponentSpace(float NewYawDegs);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (DisplayName = "SetTurretYawUpdateDirection"), Category = ITurret)
	void K2_SetTurretYawUpdateDirection(ERotationDirection NewDirection);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (DisplayName = "SetGunPitchUpdateDirection"), Category = ITurret)
	void K2_SetGunPitchUpdateDirection(ERotationDirection const NewDirection);
	// ~Main interface End

	// ~Helper Interface Begin
	FVector2D GetTargetAzimuthAndElevation(AActor* const InTarget) const
	{
		return ITurret::Execute_K2_GetTargetAzimuthAndElevation(Cast<UObject>(this), InTarget);
	}
	
	bool IsTargetReachable(float const InDistance, const FVector2D& InAzimuthAndElevation) const
	{
		return ITurret::Execute_K2_IsTargetReachable(Cast<UObject>(this), InDistance, InAzimuthAndElevation);
	}
	
	bool IsTargetReachableByElevation(const FVector2D& InAzimuthAndElevation) const
	{
		return ITurret::Execute_K2_IsTargetReachableByElevation(Cast<UObject>(this), InAzimuthAndElevation);
	}
	
	bool IsTargetReachableByDistance(float const InDistance) const
	{
		return ITurret::Execute_K2_IsTargetReachableByDistance(Cast<UObject>(this), InDistance);
	}
	
	
	bool IsAimingFinished() const
	{
		return ITurret::Execute_K2_IsAimingFinished(Cast<UObject>(this));
	}	

	ETurretAimingResult StartAimingAt(AActor* const NewTargetActor)
	{
		return ITurret::Execute_K2_StartAimingAt(Cast<UObject>(this), NewTargetActor);
	}	
	void StopAiming(const FString& InReason, ETurretAimingResult InResult)
	{
		return ITurret::Execute_K2_StopAiming(Cast<UObject>(this), InReason, InResult);
	}

	UTurretEvents* GetTurretEvents() const
	{
		return ITurret::Execute_K2_GetTurretEvents(Cast<UObject>(this));
	}

	FTurretState GetTurretState() const 
	{
		return ITurret::Execute_K2_GetTurretState(Cast<UObject>(this));
	}	

	void SetTurretState(const FTurretState& InState)
	{
		ITurret::Execute_K2_SetTurretState(Cast<UObject>(this), InState);
	}
		
	void SetTargetTurretYawInComponentSpace(float NewYawDegs)
	{
		ITurret::Execute_K2_SetTargetTurretYawInComponentSpace(Cast<UObject>(this), NewYawDegs);
	}
		
	void SetTurretYawUpdateDirection(ERotationDirection const NewDirection)
	{
		ITurret::Execute_K2_SetTurretYawUpdateDirection(Cast<UObject>(this), NewDirection);
	}
	
	void SetGunPitchUpdateDirection(ERotationDirection const NewDirection)
	{
		ITurret::Execute_K2_SetGunPitchUpdateDirection(Cast<UObject>(this), NewDirection);
	}

	void AddTargetTurretYawInComponentSpace(float const DeltaYawDegs)
	{
		if(DeltaYawDegs != 0.0F)
		{
			FTurretState State = ITurret::Execute_K2_GetTurretState(Cast<UObject>(this));
			const float NewYawDegs = State.CurrentTurretYawInComponentSpace + DeltaYawDegs;
			ITurret::Execute_K2_SetTargetTurretYawInComponentSpace(Cast<UObject>(this), NewYawDegs);
		}
	}
	
	void SetTargetGunPitchInComponentSpace(float const NewPitchDegs)
	{
		Execute_K2_SetTargetGunPitchInComponentSpace(Cast<UObject>(this), NewPitchDegs);
	}	
	void FreezeAimMovement()
	{
		FTurretState State = ITurret::Execute_K2_GetTurretState(Cast<UObject>(this));
		State.TargetGunPitchInComponentSpace = State.CurrentGunPitchInComponentSpace;
		State.TargetTurretYawInComponentSpace = State.CurrentTurretYawInComponentSpace;
	}
	void AddTargetGunPitchInComponentSpace(float const DeltaPitchDegs)
	{
		if(DeltaPitchDegs != 0.0F)
		{
			FTurretState State = ITurret::Execute_K2_GetTurretState(Cast<UObject>(this));
			const float NewPitchDegs = State.CurrentGunPitchInComponentSpace + DeltaPitchDegs;
			ITurret::Execute_K2_SetTargetGunPitchInComponentSpace(Cast<UObject>(this), NewPitchDegs);
		}
	}
	void RotateGunPitchMinimal(float const DeltaPitchDegs)
	{
		AddTargetGunPitchInComponentSpace(DeltaPitchDegs);
		const ERotationDirection NewDirection = GetMinimalPitchRotateToTargetDirection();
		SetGunPitchUpdateDirection(NewDirection);
	}
	void RotateTurretYawMinimal(float const DeltaYawDegs)
	{
		AddTargetTurretYawInComponentSpace(DeltaYawDegs);
		const ERotationDirection NewDirection = GetMinimalYawRotateToTargetDirection();
		SetTurretYawUpdateDirection(NewDirection);
	}
	void RotateGunPitchMinimalTo(float const NewPitchDegs)
	{
		SetTargetGunPitchInComponentSpace(NewPitchDegs);
		const ERotationDirection NewDirection = GetMinimalPitchRotateToTargetDirection();
		SetGunPitchUpdateDirection(NewDirection);
	}
	void RotateTurretYawMinimalTo(float const NewYawDegs)
	{
		SetTargetTurretYawInComponentSpace(NewYawDegs);
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
	// ~Helper Interface End


	// ~Main interface default implementations Begin
	virtual void K2_SetTargetGunPitchInComponentSpace_Implementation(float const NewPitchDegs)
	{
		FTurretState State = ITurret::Execute_K2_GetTurretState(Cast<UObject>(this));
		State.TargetGunPitchInComponentSpace = NewPitchDegs;
		ITurret::Execute_K2_SetTurretState(Cast<UObject>(this), State);
	}

	virtual void K2_SetGunPitchUpdateDirection_Implementation(ERotationDirection const NewDirection)
	{
		FTurretState State = ITurret::Execute_K2_GetTurretState(Cast<UObject>(this));
		State.GunPitchUpdateDirection = NewDirection;
		ITurret::Execute_K2_SetTurretState(Cast<UObject>(this), State);
	}

	virtual void K2_SetTurretYawUpdateDirection_Implementation(ERotationDirection const NewDirection)
	{
		FTurretState State = ITurret::Execute_K2_GetTurretState(Cast<UObject>(this));
		State.TurretYawUpdateDirection = NewDirection;
		ITurret::Execute_K2_SetTurretState(Cast<UObject>(this), State);
	}

	virtual void K2_SetTargetTurretYawInComponentSpace_Implementation(float const NewYawDegs)
	{
		FTurretState State = ITurret::Execute_K2_GetTurretState(Cast<UObject>(this));
		State.TargetTurretYawInComponentSpace = NewYawDegs;
		ITurret::Execute_K2_SetTurretState(Cast<UObject>(this), State);
	}
	// ~Main interface default implementations End
};


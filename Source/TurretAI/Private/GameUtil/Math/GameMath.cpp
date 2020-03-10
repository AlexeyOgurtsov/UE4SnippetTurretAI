#include "GameMath.h"
#include "Math/UnrealMathUtility.h"

float UGameMath::K2_GetFloatUpdatedToTarget(float const InDeltaTime, float const InCurrValue, float const InTargetValue, const FGameFloatUpdate& InUpdate)
{
	return GetFloatUpdatedToTarget(InDeltaTime, InCurrValue, InTargetValue, InUpdate);
}

float UGameMath::GetFloatUpdatedToTarget(float const InDeltaTime, float const InCurrValue, float const InTargetValue, const FGameFloatUpdate& InUpdate, float InErrorTolerance)
{
	float UpdatedValue = InCurrValue;
	if(FMath::IsNearlyEqual(InTargetValue, InCurrValue, InErrorTolerance))
	{
		UpdatedValue = InTargetValue;
	}
	else
	{
		float const DeltaToTarget = InTargetValue - InCurrValue;
		if(DeltaToTarget < 0)
		{
			UpdatedValue -= InDeltaTime * InUpdate.Deceleration;
			UpdatedValue = FMath::Max(InTargetValue, UpdatedValue);
		}	
		else
		{
			UpdatedValue += InDeltaTime * InUpdate.Acceleration;
			UpdatedValue = FMath::Min(InTargetValue, UpdatedValue);
		}
	}
	return UpdatedValue;
}

float UGameMath::K2_GetUnwindedDegreesUpdatedToTarget(const float InDeltaTime, const float InCurrUnwindedDegrees, const float InTargetUnwindedDegrees, const FGameFloatUpdate& InUpdate, const ERotationDirection InRotationDirection)
{
	return GetUnwindedDegreesUpdatedToTarget(InDeltaTime, InCurrUnwindedDegrees, InTargetUnwindedDegrees, InUpdate, InRotationDirection);
}

float UGameMath::GetUnwindedDegreesUpdatedToTarget(const float InDeltaTime, const float InCurrUnwindedDegrees, const float InTargetUnwindedDegrees, const FGameFloatUpdate& InUpdate, const ERotationDirection InRotationDirection, const float InErrorTolerance)
{
	if(InCurrUnwindedDegrees == InTargetUnwindedDegrees)
	{
		return InCurrUnwindedDegrees;
	}
	float WindedCurrDegs = InCurrUnwindedDegrees;
	float WindedTargetDegs = InTargetUnwindedDegrees;
	if(InCurrUnwindedDegrees < InTargetUnwindedDegrees)
	{
		if(InRotationDirection == ERotationDirection::Clockwise)
		{
			WindedCurrDegs = 360 + InCurrUnwindedDegrees;
		}
	}
	else
	{
		if(InRotationDirection == ERotationDirection::CounterClockwise)
		{
			WindedTargetDegs = 360 + InTargetUnwindedDegrees;
		}
	}
	return FMath::UnwindDegrees(GetFloatUpdatedToTarget(InDeltaTime, WindedCurrDegs, WindedTargetDegs, InUpdate, InErrorTolerance));
}

float UGameMath::GetRotationDirectionCoeff(ERotationDirection InRotationDirection)
{
	return (InRotationDirection == ERotationDirection::CounterClockwise) ? (1.0F) : (-1.0F);
}

FRotator UGameMath::ComputeXAxisAimRotation(const FVector TargetLocation)
{
	if(TargetLocation.IsNearlyZero()) return FRotator{};
	const FVector DirectionToLocation = TargetLocation.GetUnsafeNormal();

	// WARN!!! Pitch is always between (-90;90)
	const float SinPitch = DirectionToLocation.Z;
	const float PitchRads = FMath::FastAsin(SinPitch);
	const float PitchDegs = FMath::RadiansToDegrees(PitchRads);
	const float CosPitch = FMath::Cos(PitchRads);

	// Yaw is between -180; 180
	//const float SinYaw = - DirectionToLocation.Y / CosPitch;
	//const float YawDegs = FMath::RadiansToDegrees(FMath::FastAsin(SinYaw));
	const float YawRads = FMath::Atan2(DirectionToLocation.Y, DirectionToLocation.X);
	const float YawDegs = FMath::RadiansToDegrees(YawRads);
	return FRotator { PitchDegs, YawDegs, 0 };
}

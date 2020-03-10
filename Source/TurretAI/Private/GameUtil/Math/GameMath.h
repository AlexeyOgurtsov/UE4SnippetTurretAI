#pragma once

#include "GameMathTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "GameMath.generated.h"

UCLASS()
class UGameMath : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** GetFloatUpdatedToTarget*/
	UFUNCTION(BlueprintCallable, Category=GameMath, Meta=(DisplayName="GetFloatUpdatedToTarget"))
	static float K2_GetFloatUpdatedToTarget(float InDeltaTime, float InCurrValue, float InTargetValue, const FGameFloatUpdate& InUpdate);

	/** GetFloatUpdatedToTarget*/
	static float GetFloatUpdatedToTarget(float InDeltaTime, float InCurrValue, float InTargetValue, const FGameFloatUpdate& InUpdate, float InErrorTolerance = SMALL_NUMBER);

	UFUNCTION(BlueprintCallable, Category=GameMath, Meta=(DisplayName="GetDegreesUpdatedToTarget"))
	static float K2_GetUnwindedDegreesUpdatedToTarget(float InDeltaTime, float InCurrUnwindedDegrees, float InTargetUnwindedDegrees, const FGameFloatUpdate& InUpdate, ERotationDirection InRotationDirection);
	static float GetUnwindedDegreesUpdatedToTarget(float InDeltaTime, float InCurrUnwindedDegrees, float InTargetUnwindedDegrees, const FGameFloatUpdate& InUpdate, ERotationDirection InRotationDirection, float InErrorTolerance = SMALL_NUMBER);

	/**
	* @returns: +1 for COUNTER-clockwise rotation direction, -1 for clockwise
	*/
	UFUNCTION(BlueprintPure, Category=GameMath)
	float GetRotationDirectionCoeff(ERotationDirection InRotationDirection);

	/** 
	 * Computes rotation to apply to the X axis to aim at the given target.
	 * Only Pitch and Roll components are computed.
	 */
	UFUNCTION(BlueprintCallable, Category=GameMath)
	static FRotator ComputeXAxisAimRotation(FVector TargetLocation);
};

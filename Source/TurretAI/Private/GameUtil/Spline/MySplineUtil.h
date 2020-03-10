#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "MySplineUtil.generated.h"

class USplineComponent;

UCLASS()
class UMySplineUtil : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** GetDistanceAlongSplineClosestToPoint*/
	UFUNCTION(BlueprintCallable, Category=Spline)
	static float GetDistanceAlongSplineClosestToPoint(USplineComponent* Spline, const FVector& P);
	
};

#include "MySplineUtil.h"
#include "Math/UnrealMathUtility.h"
#include "Components/SplineComponent.h"

float UMySplineUtil::GetDistanceAlongSplineClosestToPoint(USplineComponent* Spline, const FVector& P)
{
	if( Spline == nullptr )
	{
		return 0.0F;
	}
	float const InputKey = Spline->FindInputKeyClosestToWorldLocation(P);
	int32 const InputPointIndex = FMath::TruncToInt(InputKey);
	float const PointDistance = Spline->GetDistanceAlongSplineAtSplinePoint(InputPointIndex);
	int32 const NumPoints = Spline->GetNumberOfSplinePoints();
	int32 const NextPointIndex = (InputPointIndex + 1) % NumPoints;
	float NextPointDistance = Spline->GetDistanceAlongSplineAtSplinePoint(NextPointIndex);
	if(InputPointIndex == (NumPoints - 1))
	{
		NextPointDistance += Spline->GetSplineLength();
	}
	float const DistanceAlongSpline = FMath::Lerp(PointDistance, NextPointDistance, (InputKey - InputPointIndex) );
	return DistanceAlongSpline;
}

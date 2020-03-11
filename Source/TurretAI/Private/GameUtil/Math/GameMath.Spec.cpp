#pragma once

#include "Tests/AutomationCommon.h"
#include "GameMath.h"

BEGIN_DEFINE_SPEC(GameMathSpec, "GameUtil.Math", EAutomationTestFlags::EngineFilter | EAutomationTestFlags::ApplicationContextMask)
	const float DEFAULT_TOLERANCE = SMALL_NUMBER;
END_DEFINE_SPEC(GameMathSpec) // GameMathSpec

void GameMathSpec::Define()
{
	Describe("GetUnwindedDegreesUpdatedToTarget", [this]()
	{

		It("Should not pass the target angle, when the increment is bigger then the rest", [this]() {
			constexpr float DeltaTime = 1.F;
			constexpr float CurrDegs = 30.F;
			constexpr float TargetDegs = 45.F;
			const FGameFloatUpdate Update = FGameFloatUpdate { 100.F };
			const float Tolerance = DEFAULT_TOLERANCE;
			TestEqual("GetUnwindedDegreesUpdatedToTarget", UGameMath::GetUnwindedDegreesUpdatedToTarget(DeltaTime, CurrDegs, TargetDegs, Update, ERotationDirection::CounterClockwise, Tolerance), TargetDegs, Tolerance);
		});

		It("It should work when the target angle is less then current", [this]() {
			constexpr float DeltaTime = 1.F;
			constexpr float CurrDegs = 45.F;
			constexpr float TargetDegs = 35.F;
			constexpr float UpdateSpeed = 10.0F;
			const FGameFloatUpdate Update = FGameFloatUpdate { UpdateSpeed };
			constexpr float ExpectedNewAngle = CurrDegs - DeltaTime * UpdateSpeed;
			const float Tolerance = DEFAULT_TOLERANCE;
			TestEqual("GetUnwindedDegreesUpdatedToTarget", UGameMath::GetUnwindedDegreesUpdatedToTarget(DeltaTime, CurrDegs, TargetDegs, Update, ERotationDirection::Clockwise, Tolerance), TargetDegs, ExpectedNewAngle);
		});

		It("It should honor the rotation direction when the target angle is bigger then current", [this]() {
			constexpr float DeltaTime = 1.F;
			constexpr float CurrDegs = 30.F;
			constexpr float TargetDegs = 45.F;
			constexpr float UpdateSpeed = 10.0F;
			const FGameFloatUpdate Update = FGameFloatUpdate { UpdateSpeed };
			constexpr float ExpectedNewAngle = CurrDegs - DeltaTime * UpdateSpeed;
			const float Tolerance = DEFAULT_TOLERANCE;
			TestEqual("GetUnwindedDegreesUpdatedToTarget", UGameMath::GetUnwindedDegreesUpdatedToTarget(DeltaTime, CurrDegs, TargetDegs, Update, ERotationDirection::Clockwise, Tolerance), ExpectedNewAngle, Tolerance);
		});

		It("It should honor the rotation direction when the target angle is less then current", [this]() {
			constexpr float DeltaTime = 1.F;
			constexpr float CurrDegs = 45.F;
			constexpr float TargetDegs = 35.F;
			constexpr float UpdateSpeed = 10.0F;
			const FGameFloatUpdate Update = FGameFloatUpdate { UpdateSpeed };
			constexpr float ExpectedNewAngle = CurrDegs + DeltaTime * UpdateSpeed;
			const float Tolerance = DEFAULT_TOLERANCE;
			TestEqual("GetUnwindedDegreesUpdatedToTarget", UGameMath::GetUnwindedDegreesUpdatedToTarget(DeltaTime, CurrDegs, TargetDegs, Update, ERotationDirection::CounterClockwise, Tolerance), TargetDegs, ExpectedNewAngle);
		});

		It("It should honor DeltaTime", [this]()
		{
			constexpr float DeltaTime = 0.5F;
			constexpr float CurrDegs = 30.F;
			constexpr float TargetDegs = 45.F;
			constexpr float UpdateSpeed = 10.0F;
			const FGameFloatUpdate Update = FGameFloatUpdate { UpdateSpeed };
			constexpr float ExpectedNewAngle = CurrDegs + DeltaTime * UpdateSpeed;
			const float Tolerance = DEFAULT_TOLERANCE;
			TestEqual("GetUnwindedDegreesUpdatedToTarget", UGameMath::GetUnwindedDegreesUpdatedToTarget(DeltaTime, CurrDegs, TargetDegs, Update, ERotationDirection::CounterClockwise, Tolerance), ExpectedNewAngle, Tolerance);
		});
	});
}

#pragma once

#include "UObject/WeakObjectPtrTemplates.h"
#include "GameUtil/Math/GameMathTypes.h"
#include "TurretTypes.generated.h"

UENUM(BlueprintType)
enum class ETurretAimingResult : uint8
{
	InProgress = 0 UMETA(DisplayName = "In Progress"),

	Success = 1 UMETA(DisplayName = "Success"),

	Aborted = 2 UMETA(DisplayName = "Aborted"),

	/**
	* Target is unreachable (too far, for example).
	*/
	TargetIsUnreachable = 3 UMETA(DisplayName = "Target is unreachable"),

	/**
	* Target is destroyed.
	*/
	TargetIsDestroyed = 4 UMETA(DisplayName = "Target is destroyed"),
};


USTRUCT(BlueprintType)
struct FTurretAimState
{
	GENERATED_BODY()

	UPROPERTY()
	TWeakObjectPtr<AActor> TargetActor = nullptr;
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(ShowOnlyInnerProperties))
	FTurretAimState Aim;
};


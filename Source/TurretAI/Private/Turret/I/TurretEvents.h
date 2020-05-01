#pragma once

#include "TurretTypes.h"
#include "TurretEvents.generated.h"

class AActor;

USTRUCT(BlueprintType)
struct FOnTurretAimingFinishedDelegateArgs
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Aiming)
	ETurretAimingResult Result;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Aiming)
	AActor* TargetActor = nullptr;
	
	FOnTurretAimingFinishedDelegateArgs()
	{
	}
	FOnTurretAimingFinishedDelegateArgs(ETurretAimingResult InResult, AActor* InTargetActor)
	: Result(InResult)
	, TargetActor(InTargetActor)
	{
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAimingFinishedDelegate, const FOnTurretAimingFinishedDelegateArgs&, InArgs);

UCLASS()
class UTurretEvents : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FOnAimingFinishedDelegate OnAimingFinished;
};

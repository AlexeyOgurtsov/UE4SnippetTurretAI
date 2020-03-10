#pragma once

#include "UObject/Interface.h"
#include "MyPawnEvents.h"
#include "IMyPawnInterface.generated.h"

class UPawnSensingComponent;

USTRUCT(BlueprintType, Category=Damage)
struct FMyHitState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Hits = 100.0F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHits = 100.0F;

	FMyHitState() {}
	FMyHitState(float const InHits) :
		Hits (InHits)
	{
	}
};


UINTERFACE(BlueprintType)
class UMyPawnInterface : public UInterface
{
	GENERATED_BODY()

public:
};
		

class IMyPawnInterface
{
	GENERATED_BODY()

public:
	// ~HitState Begin
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=IMyPawnInterface)
	FMyHitState GetHitState() const;
	// ~HitState End

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=IMyPawnInterface)
	UMyPawnEvents* GetEvents() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=IMyPawnInterface)
	UPawnSensingComponent* GetSensingComponent() const;
};

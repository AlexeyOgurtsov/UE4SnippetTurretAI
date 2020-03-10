#pragma once

#include "MyPawnEvents.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMyPawnDamageStateChanged);

UCLASS()
class UMyPawnEvents : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FMyPawnDamageStateChanged OnDamageStateChanged;
};

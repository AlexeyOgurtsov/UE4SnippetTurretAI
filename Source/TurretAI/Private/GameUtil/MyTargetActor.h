#pragma once

/**
* To be copied to the destination and changed.
*/

#include "Util/TestUtil/TUVisibleActor.h"
#include "MyTargetActor.generated.h"

class UDamageType;

UCLASS()
class AMyTargetActor : public ATUVisibleActor
{
	GENERATED_BODY()

public:
	AMyTargetActor();

	virtual void ReceiveAnyDamage_Implementation(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	virtual void BeginPlay() override;
};

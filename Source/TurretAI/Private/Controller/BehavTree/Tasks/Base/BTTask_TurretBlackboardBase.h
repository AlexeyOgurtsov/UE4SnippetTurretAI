#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_TurretBlackboardBase.generated.h"

class ITurret;

UCLASS(BlueprintType)
class UBTTask_TurretBlackboardBase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_TurretBlackboardBase();

protected:
	ITurret* GetTurretFrom(UBehaviorTreeComponent& BTComp) const;
};

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TurretBase.generated.h"

class ITurret;

UCLASS(BlueprintType)
class UBTTask_TurretBase : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_TurretBase();

protected:
	ITurret* GetTurretFrom(UBehaviorTreeComponent& BTComp) const;
};

#pragma once

#include "Controller/BehavTree/Tasks/Base/BTTask_TurretBlackboardBase.h"
#include "BTTask_TurretAimAt.generated.h"

struct FBTTurretAimAtTaskMemory
{
};

UCLASS(BlueprintType)
class UBTTask_TurretAimAt : public UBTTask_TurretBlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_TurretAimAt();

	// ~UBTTaskNode Begin
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual uint16 GetInstanceMemorySize() const override;
	// ~UBTTaskNode End
};

#include "BTTask_TurretAimAt.h"
#include "Turret\I\ITurret.h"
#include "Turret\I\TurretLib.h"
#include "Util\Core\LogUtilLib.h"

UBTTask_TurretAimAt::UBTTask_TurretAimAt()
{
	NodeName = "TurretAimAt";
}

EBTNodeResult::Type UBTTask_TurretAimAt::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto MyMem = CastInstanceNodeMemory<FBTTurretAimAtTaskMemory>(NodeMemory);
	return EBTNodeResult::Type::Failed; // @TODO
}

void UBTTask_TurretAimAt::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// @TODO
}

uint16 UBTTask_TurretAimAt::GetInstanceMemorySize() const
{
	return sizeof(FBTTurretAimAtTaskMemory);
}

#include "BTTask_TurretBlackboardBase.h"
#include "BTTurretUtilLib.h"
#include "Util\Core\LogUtilLib.h"

UBTTask_TurretBlackboardBase::UBTTask_TurretBlackboardBase()
{
}

ITurret* UBTTask_TurretBlackboardBase::GetTurretFrom(UBehaviorTreeComponent& BTComp) const
{
	return UBTTurretUtilLib::GetTurretFrom(&BTComp);
}

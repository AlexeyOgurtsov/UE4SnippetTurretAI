#include "BTTask_TurretBase.h"
#include "BTTurretUtilLib.h"
#include "Util\Core\LogUtilLib.h"

UBTTask_TurretBase::UBTTask_TurretBase()
{
}

ITurret* UBTTask_TurretBase::GetTurretFrom(UBehaviorTreeComponent& BTComp) const
{
	return UBTTurretUtilLib::GetTurretFrom(&BTComp);
}

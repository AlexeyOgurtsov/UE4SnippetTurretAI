#include "BTTurretUtilLib.h"
#include "Turret\I\ITurret.h"

#include "AIController.h"
#include "BehaviorTree\BehaviorTreeComponent.h"

TScriptInterface<ITurret> UBTTurretUtilLib::K2_GetTurretFromBTComp(UBehaviorTreeComponent* Comp)
{
	return Cast<UObject>(GetTurretFrom(Comp));
}

ITurret* UBTTurretUtilLib::GetTurretFrom(UBehaviorTreeComponent* Comp)
{
	if(Comp == nullptr) 
	{
		return nullptr;
	}
	if(AAIController* AIController = Comp->GetAIOwner())
	{
		return Cast<ITurret>(AIController->GetPawn());
	}
	else
	{
		return nullptr;
	}
}

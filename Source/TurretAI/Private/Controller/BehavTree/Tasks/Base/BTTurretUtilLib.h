#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/ScriptInterface.h"
#include "BTTurretUtilLib.generated.h"

class UBehaviorTreeComponent;
class ITurret;

UCLASS(BlueprintType)
class UBTTurretUtilLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category=TurretBT, Meta=(DisplayName=GetTurretFromBTComp))
	static TScriptInterface<ITurret> K2_GetTurretFromBTComp(UBehaviorTreeComponent* Comp);

	static ITurret* GetTurretFrom(UBehaviorTreeComponent* Comp);
};

#pragma once

#include "I/ITurret.h"
#include "Animation/AnimInstance.h"
#include "TurretAnimInstanceBase.generated.h"

UCLASS()
class UTurretAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

public:
	// ~UAnimInstance Begin
	void NativeInitializeAnimation() override;
	void NativeUpdateAnimation(float DeltaTimeX) override;
	// ~UAnimInstance End

protected:
	UFUNCTION(BlueprintGetter, Category = Turret)
	TScriptInterface<ITurret> GetTurret() const { return Turret; }
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	FTurretState TurretState;

private:
	UPROPERTY()
	TScriptInterface<ITurret> Turret;

	void InitializeLinkToTurret();
};

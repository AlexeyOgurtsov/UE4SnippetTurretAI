#pragma once

#include "MyAIControllerBase.h"
#include "Turret\I\TurretEvents.h"

#include "UObject/ScriptInterface.h"

#include "MyTurretControllerBase.generated.h"

class ITurret;

class UBehaviorTree;

UCLASS()
class AMyTurretControllerBase : public AMyAIControllerBase
{
	GENERATED_BODY()

public:
	AMyTurretControllerBase();

	// ~AActor Begin
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	// ~AActor End

	// ~Turret Access Begin
	UFUNCTION(BlueprintPure, Category = Turret)
	TScriptInterface<ITurret> GetTurret() const;

	UFUNCTION(BlueprintPure, Category = Turret)
	TScriptInterface<ITurret> GetTurretChecked() const;
	// ~Turret Access End
	
	// ~Turret-related event handlers Begin
	virtual void OnSeePawn_Implementation(APawn* InPawn);
	virtual void OnDamageStateChanged_Implementation();
	// ~Turret-related event handlers End

protected:
	UFUNCTION(BlueprintNativeEvent, Category = Aiming)
	void OnAimingFinished(const FOnTurretAimingFinishedDelegateArgs& InArgs);
	virtual void OnAimingFinished_Implementation(const FOnTurretAimingFinishedDelegateArgs& InArgs);

	UFUNCTION(BlueprintNativeEvent, Category = Events)
	void BindToEvents(const TScriptInterface<ITurret>& InTurret);
	virtual void BindToEvents_Implementation(const TScriptInterface<ITurret>& InTurret);

	UFUNCTION(BlueprintNativeEvent, Category = Events)
	void UnbindFromEvents(const TScriptInterface<ITurret>& InTurret);
	virtual void UnbindFromEvents_Implementation(const TScriptInterface<ITurret>& InTurret);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true), Category = "Behavior")
	UBehaviorTree* BehavTree = nullptr;

	FString PrefixString;
};

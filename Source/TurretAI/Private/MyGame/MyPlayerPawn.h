#pragma once

/**
* To be copied to the destination and changed.
*/

#include "Util/TestUtil/TUPawn.h"
#include "Util/Core/Log/MyLoggingTypes.h"
#include "PawnBase/IMyPawnInterface.h"
#include "MyPlayerPawn.generated.h"

class UMyPawnImpl;

UCLASS()
class AMyPlayerPawn 
: public ATUPawn
, public IMyPawnInterface
{
	GENERATED_BODY()

	// ~Framework Begin
	virtual void MyBeginPlay_Implementation() override;
	// ~Framework End

	// ~Access helpers Begin
	UFUNCTION(BlueprintPure, Category = Controller)
	AMyPlayerController* GetMyPC() const;

	UFUNCTION(BlueprintPure, Category = Controller)
	AMyPlayerController* GetMyPCLogged(ELogFlags InLogFlags = ELogFlags::None) const;

	/**
	* Checks that the given pawn NOT null.
	*/
	UFUNCTION(BlueprintPure, Category = Controller)
	AMyPlayerController* GetMyPCChecked() const;
	// ~Access helpers End
	
	// ~ITUPawnActions Begin
	// This section contains notifying functions about the controller's actions
	virtual void OnController_Axis_LookPitch_Implementation(float InAmount) override;
	virtual void OnController_Axis_LookYaw_Implementation(float InAmount) override;
	virtual void OnController_Axis_Forward_Implementation(float InAmount) override;
	virtual void OnController_Axis_Right_Implementation(float InAmount) override;
	virtual void OnController_Axis_Up_Implementation(float InAmount) override;
	virtual void OnController_Action_Use_Implementation() override;
	virtual void OnController_Action_UseTwo_Implementation() override;
	virtual void OnController_Action_UseThree_Implementation() override;
	virtual void PawnStartFire(uint8 FireModeNum) override;
	virtual void OnController_Action_Fire_Implementation() override;
	virtual void OnController_Action_FireTwo_Implementation() override;
	virtual void OnController_Action_FireThree_Implementation() override;
	virtual void OnController_Action_SelectZero_Implementation() override;
	virtual void OnController_Action_SelectOne_Implementation() override;
	virtual void OnController_Action_SelectTwo_Implementation() override;
	virtual void OnController_Action_SelectThree_Implementation() override;
	virtual void OnController_Action_SelectFour_Implementation() override;
	virtual void OnController_Action_SelectFive_Implementation() override;
	virtual void OnController_Action_SelectSix_Implementation() override;
	virtual void OnController_Action_SelectSeven_Implementation() override;
	virtual void OnController_Action_SelectEight_Implementation() override;
	virtual void OnController_Action_SelectNine_Implementation() override;
	virtual void OnController_Action_OpenGameMenu_Implementation() override;
	virtual void OnController_Action_CloseGameMenu_Implementation() override;
	virtual void OnController_Action_DebugOne_Implementation() override;
	virtual void OnController_Action_DebugTwo_Implementation() override;
	virtual void OnController_Action_DebugThree_Implementation() override;

	// ~ITUPawnActions End
	// ~ AActor Begin
	virtual float TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	// ~ AActor End
	
	// ~ IMyPawnBase Begin
	virtual FMyHitState GetHitState_Implementation() const override;
	virtual UMyPawnEvents* GetEvents_Implementation() const override;
	virtual UPawnSensingComponent* GetSensingComponent_Implementation() const override { return nullptr; }
	// ~ IMyPawnBase End

public:
	AMyPlayerPawn();

private:
	// ~Motion Begin
	void InitMovement();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Motion, Meta=(AllowPrivateAccess = true))
	UPawnMovementComponent *Movement = nullptr;
	// ~Motion End

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Impl, Meta=(AllowPrivateAccess = true))
	UMyPawnImpl* Impl = nullptr;
	
};

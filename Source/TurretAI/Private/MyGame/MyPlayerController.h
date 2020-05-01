#pragma once

/**
* To be copied to the destination and changed.
*/

#include "Util/TestUtil/TUPlayerController.h"
#include "Turret/I/TurretTypes.h"
#include "Turret/I/TurretEvents.h"
#include "Util/Core/Log/MyLoggingTypes.h"
#include "MyPlayerController.generated.h"

class UPossessControllerComponent;

class AMyPlayerPawn;
class ITurret;

UCLASS()
class AMyPlayerController : public ATUPlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

	// ~AActor Begin
	virtual void BeginPlay() override;
	// ~AActor End
	
	// ~AController Begin
	virtual void OnUnPossess() override;
	virtual void OnPossess(APawn* InPawn) override;	
	// ~AController End

	// ~Access helpers Begin
	UFUNCTION(BlueprintPure, Category = Pawn)
	AMyPlayerPawn* GetMyPawn() const;

	UFUNCTION(BlueprintPure, Category = Pawn)
	AMyPlayerPawn* GetMyPawnLogged(ELogFlags InLogFlags = ELogFlags::None) const;

	/**
	* Checks that the given pawn NOT null.
	*/
	UFUNCTION(BlueprintPure, Category = Pawn)
	AMyPlayerPawn* GetMyPawnChecked() const;
	// ~Access helpers End

	/** GetPossessComponent*/
	UFUNCTION(BlueprintPure, Category=Possess)
	UPossessControllerComponent* GetPossessComponent() const { return PossessComponent; }

protected:
	// ~ITurret-related begin
	virtual void OnUnPossessTurret(ITurret* Turret);
	virtual void OnPossessTurret(ITurret* Turret);

	UFUNCTION()
	virtual void OnAimFinished(const FOnTurretAimingFinishedDelegateArgs& InAimingFinished);
	// ~ITurret-related end


	// ~Controller-level action handlers Begin
	virtual void Axis_LookPitch(APawn* P, float InAmount) override;
	virtual void Axis_LookYaw(APawn* P, float InAmount) override;
	virtual void Axis_Forward(APawn* P, float InAmount) override;
	virtual void Axis_Right(APawn* P, float InAmount) override;
	virtual void Axis_Up(APawn* P, float InAmount) override;
	virtual void Action_Use() override;
	virtual void Action_UseTwo() override;
	virtual void Action_UseThree() override;
	virtual void Action_Fire() override;
	virtual void Action_FireTwo() override;
	virtual void Action_FireThree() override;
	virtual void Action_SelectZero() override;
	virtual void Action_SelectOne() override;
	virtual void Action_SelectTwo() override;
	virtual void Action_SelectThree() override;
	virtual void Action_SelectFour() override;
	virtual void Action_SelectFive() override;
	virtual void Action_SelectSix() override;
	virtual void Action_SelectSeven() override;
	virtual void Action_SelectEight() override;
	virtual void Action_SelectNine() override;
	virtual void Action_OpenGameMenu() override;
	virtual void Action_CloseGameMenu() override;
	virtual void Action_DebugOne() override;
	virtual void Action_DebugTwo() override;
	virtual void Action_DebugThree() override;
	// ~Controller-level action handlers End

private:
	/** PossessComponent*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Possess)
	UPossessControllerComponent* PossessComponent = nullptr;
};

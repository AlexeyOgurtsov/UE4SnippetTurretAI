#pragma once

/**
* Actor that has collision and mesh.
*/

#include "GameFramework/Pawn.h"
#include "I/ITurret.h"
#include "Util/TestUtil/I/ITUPawnActions.h"
#include "PawnBase/IMyPawnInterface.h"
#include "Util/Core/Log/MyLoggingTypes.h"
#include "TurretPawnBase.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USceneComponent;
class USkeletalMeshComponent;
class USphereComponent;
class AMyAIControllerBase;
class ITUController;
class UMyPawnImpl;

class UPawnSensingComponent;

UCLASS()
class ATurretPawnBase : 
	public APawn
,	public IMyPawnInterface
,	public ITUPawnActions
,	public ITurret
{
	GENERATED_BODY()

public:
	ATurretPawnBase();

	// Helper getters Begin
	AMyAIControllerBase* GetAIControllerBase() const;
	// Helper getters End

	// ~ AActor Begin
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Tick(float DeltaSeconds) override;
	// ~ AActor End
	
	// ~ IMyPawnBase Begin
	virtual FMyHitState GetHitState_Implementation() const override;
	virtual UMyPawnEvents* GetEvents_Implementation() const override;
	virtual UPawnSensingComponent* GetSensingComponent_Implementation() const override;
	// ~ IMyPawnBase End
	//
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
	virtual void OnController_Action_DebugOne_Implementation() override;
	virtual void OnController_Action_DebugTwo_Implementation() override;
	virtual void OnController_Action_DebugThree_Implementation() override;
	// ~ITUPawnActions End

	// ~ ITurret Begin
	virtual FTurretState K2_GetTurretState_Implementation() const override { return TurretState; }
	virtual void K2_SetTurretState_Implementation(const FTurretState& InState) override { TurretState = InState; }
	// ~ ITurret End

	UFUNCTION(BlueprintPure, Category = Components)
	USceneComponent* GetRootSceneComponent() const { return RootSceneComponent; }

	UFUNCTION(BlueprintPure, Category = Camera)
	UCameraComponent* GetCamera() const { return Camera; }

	UFUNCTION(BlueprintPure, Category = Visual)
	USkeletalMeshComponent* GetMesh() const { return Mesh; }

	UFUNCTION(BlueprintPure, Category = Collision)
	USphereComponent* GetProxSphere() const { return ProxSphere; }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components, Meta=(AllowPrivateAccess = true))
	USceneComponent* RootSceneComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera, Meta=(AllowPrivateAccess = true))
	UCameraComponent* Camera = nullptr;
	void InitCameraAndSpringArm(USceneComponent* InAttachTo);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera, Meta=(AllowPrivateAccess = true))
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Visual, Meta=(AllowPrivateAccess = true))
	USkeletalMeshComponent* Mesh = nullptr;
	void InitMesh(USceneComponent* InAttachTo);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Collision, Meta=(AllowPrivateAccess = true))
	USphereComponent* ProxSphere = nullptr;
	void InitProxSphere(USceneComponent* InAttachTo);
	
	/** GetSensing*/
	UFUNCTION(BlueprintPure, Category=Sensing)
	UPawnSensingComponent* GetSensing() const
	{
		return Sensing;
	}

	// ~Controller Begin
	UFUNCTION(BlueprintPure, Category = Controller, Meta=(DisplayName="GetTUController"))
	TScriptInterface<ITUController> K2GetTUController() const;

	UFUNCTION(BlueprintPure, Category = Controller, Meta=(DisplayName="GetTUControllerLogged"))
	TScriptInterface<ITUController> K2GetTUControllerLogged(ELogFlags InLogFlags = ELogFlags::None) const;

	UFUNCTION(BlueprintPure, Category = Controller, Meta=(DisplayName="GetTUControllerChecked"))
	TScriptInterface<ITUController> K2GetTUControllerChecked() const;

	ITUController* GetTUController() const;
	ITUController* GetTUControllerLogged(ELogFlags InLogFlags = ELogFlags::None) const;
	ITUController* GetTUControllerChecked() const ;

	UFUNCTION(BlueprintPure, Category = Controller)
	AController* GetControllerLogged(ELogFlags InLogFlags = ELogFlags::None) const;

	UFUNCTION(BlueprintPure, Category = Controller)
	AController* GetControllerChecked() const;

	UFUNCTION(BlueprintPure, Category = Controller)
	APlayerController* GetPC() const;

	UFUNCTION(BlueprintPure, Category = Controller)
	APlayerController* GetPCLogged(ELogFlags InLogFlags = ELogFlags::None) const;

	UFUNCTION(BlueprintPure, Category = Controller)
	APlayerController* GetPCChecked() const;
	// ~Controller End

private:
	// ~Sensing Begin
	/** Sensing*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	UPawnSensingComponent* Sensing = nullptr;

	/** OnSeePawn*/
	UFUNCTION(BlueprintCallable, Category=Sensing)
	void OnSeePawn(APawn* InPawn);

	void InitializeSensingComponent();	
	// ~Sensing End
	
	// ~ ITurret Begin
	UPROPERTY(EditAnywhere, Meta=(ShowOnlyInnerProperties))
	FTurretState TurretState;

	void TickTurret(float DeltaSeconds);
	// ~ ITurret End
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	UMyPawnImpl* Impl = nullptr;
};

#pragma once

/**
* Actor that has collision and mesh.
*/

#include "GameFramework/Pawn.h"
#include "PawnBase/IMyPawnInterface.h"
#include "TurretPawnBase.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USceneComponent;
class USkeletalMeshComponent;
class USphereComponent;
class AMyAIControllerBase;

class UMyPawnImpl;

class UPawnSensingComponent;

UCLASS()
class ATurretPawnBase : 
	public APawn
,	public IMyPawnInterface
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
	// ~ AActor End
	
	// ~ IMyPawnBase Begin
	virtual FMyHitState GetHitState_Implementation() const override;
	virtual UMyPawnEvents* GetEvents_Implementation() const override;
	virtual UPawnSensingComponent* GetSensingComponent_Implementation() const override;
	// ~ IMyPawnBase End

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
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	UMyPawnImpl* Impl = nullptr;
};

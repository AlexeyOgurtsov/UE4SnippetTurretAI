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
	//
	//
	
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

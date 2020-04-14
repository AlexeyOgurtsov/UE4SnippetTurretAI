#pragma once

#include "PawnBase/IMyPawnInterface.h"
#include "Engine/EngineTypes.h"
#include "MyPawnImpl.generated.h"

class AActor;
class AController;
class UMyPawnEvents;

class UWeaponComponent;

UCLASS()
class UMyPawnImpl : public UObject
{
	GENERATED_BODY()

public:
	UMyPawnImpl();

	static UMyPawnImpl* CreateInitialized(AActor* InOwner, const FName InName, UWeaponComponent* InWeaponComponent = nullptr);
	AActor* GetOwner() const { return Owner; }
	
	float TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	// ~ IMyPawnBase Begin
	UPROPERTY(EditAnywhere, category=HitState)
	FMyHitState HitState;

	UPROPERTY(EditAnywhere, category=Events)
	UMyPawnEvents* MyEvents = nullptr;
	// ~ IMyPawnBase End

	/** GetWeaponComponent*/
	UFUNCTION(BlueprintPure, Category=Weapon)
	UWeaponComponent* GetWeaponComponent() const { return WeaponComponent; }
	
private:
	void SetNewDamageState(float InNewDamage, bool bInNotify = true);
	AActor* Owner = nullptr;

	/** WeaponComponent*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	UWeaponComponent* WeaponComponent = nullptr;
};

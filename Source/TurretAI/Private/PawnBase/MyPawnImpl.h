#pragma once

#include "PawnBase/IMyPawnInterface.h"
#include "Engine/EngineTypes.h"
#include "MyPawnImpl.generated.h"

class AActor;
class AController;
class UMyPawnEvents;

UCLASS()
class UMyPawnImpl : public UObject
{
	GENERATED_BODY()

public:
	UMyPawnImpl();

	static UMyPawnImpl* CreateInitialized(AActor* InOwner, const FName InName);
	AActor* GetOwner() const { return Owner; }
	
	float TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	// ~ IMyPawnBase Begin
	UPROPERTY(EditAnywhere, category=HitState)
	FMyHitState HitState;

	UPROPERTY(EditAnywhere, category=Events)
	UMyPawnEvents* MyEvents = nullptr;
	// ~ IMyPawnBase End

private:
	void SetNewDamageState(float InNewDamage, bool bInNotify = true);
	AActor* Owner = nullptr;
};

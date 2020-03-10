#pragma once

#include "Turret/TurretPawnBase.h"
#include "SimpleTurretPawn.generated.h"

UCLASS()
class ASimpleTurretPawn : 
	public ATurretPawnBase
{
	GENERATED_BODY()

public:
	ASimpleTurretPawn();

	// Helper getters Begin
	AMyAIControllerBase* GetAIControllerBase() const;
	// Helper getters End

	// ~ AActor Begin
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	// ~ AActor End
};

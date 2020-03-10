#include "SimpleTurretPawn.h"

#include "Util/Core/LogUtilLib.h"

ASimpleTurretPawn::ASimpleTurretPawn()
{
}

// ~ AActor Begin
void ASimpleTurretPawn::BeginPlay() 
{
	Super::BeginPlay();
}

float ASimpleTurretPawn::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float result = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return result;
}
// ~ AActor End

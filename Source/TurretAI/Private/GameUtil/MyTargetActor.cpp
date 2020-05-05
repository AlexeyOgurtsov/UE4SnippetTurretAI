#include "MyTargetActor.h"
#include "Util/Core/LogUtilLib.h"

#include "GameFramework/DamageType.h"

AMyTargetActor::AMyTargetActor()
{
	SetCanBeDamaged(true);
}

void AMyTargetActor::BeginPlay()
{
	M_LOGFUNC();
	Super::BeginPlay();
}

void AMyTargetActor::ReceiveAnyDamage_Implementation(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{	
	M_LOG(TEXT("Damage received: Damage=%d, DamageType=\"%s\""), Damage, DamageType ? *DamageType->GetClass()->GetName() : TEXT("nullptr"));	
}

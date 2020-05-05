#include "MyAIControllerBase.h"
#include "PawnBase/IMyPawnInterface.h"

#include "Util/Core/AI/AIUtil.h"
#include "Util/Core/LogUtilLib.h"

#include "Perception/PawnSensingComponent.h"
#include "Perception/AIPerceptionComponent.h"


AMyAIControllerBase::AMyAIControllerBase()
{
}

void AMyAIControllerBase::OnPawnBeginPlay(APawn* const InPawn)
{
	M_LOGFUNC();
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("InPawn"), InPawn);
}

void AMyAIControllerBase::BeginPlay()
{
	M_LOGFUNC();
	Super::BeginPlay();
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("Perception"), GetPerceptionComponent());
}

void AMyAIControllerBase::Tick(float const DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(NumTicks == 0)
	{
		M_LOG(TEXT("AI Controller Tick, DeltaSeconds=%f"), DeltaSeconds);
		ULogUtilLib::LogKeyedNameClassSafeC(TEXT("Perception (In Tick)"), GetPerceptionComponent());
	}
	NumTicks++;
}

void AMyAIControllerBase::OnMoveCompleted(FAIRequestID const RequestID, const FPathFollowingResult& Result)
{
	M_LOGFUNC();
	Super::OnMoveCompleted(RequestID, Result);
	M_LOG(TEXT("RequestID: %d"), RequestID);
	UAIUtil::LogPathFollowingResult(FString(TEXT("Result")), Result);
}

void AMyAIControllerBase::SetPawn(APawn* const InPawn)
{
	M_LOGFUNC();
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("GetPawn() Before SUPER"), GetPawn());
	Super::SetPawn(InPawn);
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("GetPawn() After SUPER"), GetPawn());
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("InPawn"), InPawn);
}

void AMyAIControllerBase::OnPossess(APawn* const InPawn)
{
	M_LOGFUNC();
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("GetPawn() Before SUPER"), GetPawn());
	Super::OnPossess(InPawn);
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("GetPawn() After SUPER"), GetPawn());
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("InPawn"), InPawn);
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("Perception"), GetPerceptionComponent());
	if(Cast<IMyPawnInterface>(InPawn) != nullptr)
	{
		M_LOG(TEXT("New pawn is valid IMyPawnInterface instance"));
		IMyPawnInterface::Execute_GetEvents(InPawn)->OnDamageStateChanged.AddDynamic(this, &AMyAIControllerBase::OnDamageStateChanged);
		if(UPawnSensingComponent* Sensing = IMyPawnInterface::Execute_GetSensingComponent(InPawn))
		{
			M_LOG(TEXT("Sensing component found, binding delegates"));
			Sensing->OnSeePawn.AddDynamic(this, &AMyAIControllerBase::OnSeePawn);
		}
	}
}

void AMyAIControllerBase::OnUnPossess()
{
	M_LOGFUNC();
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("GetPawn() Before SUPER"), GetPawn());
	Super::OnUnPossess();
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("GetPawn() After SUPER"), GetPawn());
}

void AMyAIControllerBase::PawnPendingDestroy(APawn* InPawn)
{
	M_LOGFUNC();
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("GetPawn() Before SUPER"), GetPawn());
	Super::PawnPendingDestroy(InPawn);
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("GetPawn() After SUPER"), GetPawn());
}

TScriptInterface<IMyPawnInterface> AMyAIControllerBase::K2_GetMyPawn() const
{
	return TScriptInterface<IMyPawnInterface>(GetPawn());
}

IMyPawnInterface* AMyAIControllerBase::GetMyPawn() const
{
	return Cast<IMyPawnInterface>(GetPawn());
}

UPawnSensingComponent* AMyAIControllerBase::GetSensingComponent() const
{
	if(IMyPawnInterface* P = GetMyPawn())
	{
		return IMyPawnInterface::Execute_GetSensingComponent(Cast<UObject>(P));
	}
	else
	{
		return nullptr;
	}
}

float AMyAIControllerBase::GetHitPoints() const
{
	if(IMyPawnInterface* P = GetMyPawn())
	{
		return IMyPawnInterface::Execute_GetHitState(Cast<UObject>(P)).Hits;
	}
	else
	{
		return 0.0F;
	}
}

float AMyAIControllerBase::GetMaxHitPoints() const
{
	if(IMyPawnInterface* P = GetMyPawn())
	{
		return IMyPawnInterface::Execute_GetHitState(Cast<UObject>(P)).MaxHits;
	}
	else
	{
		return 0.0F;
	}
}

void AMyAIControllerBase::OnSeePawn_Implementation(APawn* InPawn)
{
	bool const bSeenSamePawn = (LastSeenPawn == InPawn);
	bool const bShouldLog = bAlwaysLogSeePawn || ( ! bSeenSamePawn );

	M_LOGFUNC_IF(bShouldLog);

	LastSeenPawn = InPawn;
}

void AMyAIControllerBase::OnDamageStateChanged_Implementation()
{
	M_LOGFUNC();
}

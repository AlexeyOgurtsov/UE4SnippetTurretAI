#include "MyAIController.h"
#include "Util/Core/LogUtilLib.h"
#include "Util/Core/AI/AIUtil.h"
#include "Kismet/GameplayStatics.h"

AMyAIController::AMyAIController()
{
}

void AMyAIController::PostInitProperties()
{
	Super::PostInitProperties();
}

void AMyAIController::BeginPlay()
{
	M_LOGFUNC();
	Super::BeginPlay();
}

void AMyAIController::OnPawnBeginPlay(APawn* InPawn)
{
	Super::OnPawnBeginPlay(InPawn);
}

void AMyAIController::OnPossess(APawn* const InPawn)
{
	M_LOGFUNC();
	Super::OnPossess(InPawn);
}

void AMyAIController::OnMoveCompleted(FAIRequestID InRequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(InRequestID, Result);
	// @TODO
}

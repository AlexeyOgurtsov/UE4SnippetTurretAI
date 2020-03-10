#pragma once

#include "MyAIControllerBase.h"
#include "AITypes.h"
#include "MyAIController.generated.h"

UCLASS()
class AMyAIController : public AMyAIControllerBase
{
	GENERATED_BODY()

public:
	AMyAIController();

	virtual void OnPawnBeginPlay(APawn* InPawn) override;

	// ~AActor Begin
	virtual void BeginPlay() override;
	virtual void PostInitProperties() override;
	// ~AActor End

	// ~AAIController Begin
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnMoveCompleted(FAIRequestID InRequestID, const FPathFollowingResult& Result) override;
	// ~AAIController Begin
};

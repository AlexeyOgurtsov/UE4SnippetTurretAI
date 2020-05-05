#pragma once

#include "AIController.h"
#include "MyAIControllerBase.generated.h"

class IMyPawnBase;
class UPawnSensingComponent;

UCLASS()
class AMyAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	AMyAIControllerBase();

	virtual void BeginPlay() override;

	virtual void OnPawnBeginPlay(APawn* InPawn);

	// ~AAIController Begin
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	// ~AAIController End

	// ~AActor Begin
	virtual void Tick(float DeltaSeconds) override;
	// ~AActor End

protected:
	// ~AController Begin
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void PawnPendingDestroy(APawn* InPawn) override;
	// ~AController End
	
	// ~AAIController Begin
	virtual void SetPawn(APawn* InPawn) override;
	// ~AAIController End

	UFUNCTION(BlueprintCallable, Category = MyPawn, Meta=(DisplayName=GetMyPawn))
	TScriptInterface<IMyPawnInterface> K2_GetMyPawn() const;

	IMyPawnInterface* GetMyPawn() const;

	UFUNCTION(BlueprintCallable, Category = MyPawn)
	UPawnSensingComponent* GetSensingComponent() const;

	UFUNCTION(BlueprintCallable, Category = MyPawn)
	float GetHitPoints() const;

	UFUNCTION(BlueprintCallable, Category = MyPawn)
	float GetMaxHitPoints() const;

	UFUNCTION(BlueprintNativeEvent, Category = Perception)
	void OnSeePawn(APawn* InPawn);
	virtual void OnSeePawn_Implementation(APawn* InPawn);

	UFUNCTION(BlueprintNativeEvent, Category = Damage)
	void OnDamageStateChanged();
	virtual void OnDamageStateChanged_Implementation();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyPawn, Meta=(AllowPrivateAccess = true))
	bool bAlwaysLogSeePawn = false;

	UPROPERTY()
	APawn* LastSeenPawn = nullptr;

	UPROPERTY()
	int32 NumTicks = 0;
};

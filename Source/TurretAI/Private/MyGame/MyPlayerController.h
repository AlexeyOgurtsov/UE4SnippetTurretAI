#pragma once

/**
* To be copied to the destination and changed.
*/

#include "Util/TestUtil/TUPlayerController.h"
#include "Util/Core/Log/MyLoggingTypes.h"
#include "MyPlayerController.generated.h"

class AMyPlayerPawn;

UCLASS()
class AMyPlayerController : public ATUPlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

	// ~AActor Begin
	virtual void BeginPlay() override;
	// ~AActor End

	// ~Access helpers Begin
	UFUNCTION(BlueprintPure, Category = Pawn)
	AMyPlayerPawn* GetMyPawn() const;

	UFUNCTION(BlueprintPure, Category = Pawn)
	AMyPlayerPawn* GetMyPawnLogged(ELogFlags InLogFlags = ELogFlags::None) const;

	/**
	* Checks that the given pawn NOT null.
	*/
	UFUNCTION(BlueprintPure, Category = Pawn)
	AMyPlayerPawn* GetMyPawnChecked() const;
	// ~Access helpers End

private:
};

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "PossessTypes.h"
#include "PossessLib.generated.h"

UCLASS()
class UPossessLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Tries to possess the given pawn by the given controller.
	*
	* @returns: true if successfully possessed.
	*/
	UFUNCTION(BlueprintCallable, Category=UPossessLib)
	static bool TryPossess(AController* Controller, APawn* Pawn, const FPossessProps& Props, EMyPossessFlags Flags = EMyPossessFlags::Default);

	/**
	* Check conditions, provides the feedback.
	*/
	UFUNCTION(BlueprintCallable, Category=UPossessLib)
	static bool PossessConditionsValid(AController* Controller, APawn* Pawn, const FPossessProps& Props, EMyPossessFlags Flags = EMyPossessFlags::Default);

	/**
	* Performs possession of the given pawn by the given controller.
	* WARNING!!! Always possesses, whether already controlled or not.
	*/
	UFUNCTION(BlueprintCallable, Category=UPossessLib)
	static void DoRePossess(AController* Controller, APawn* Pawn, const FDoPossessProps& Props, EMyPossessFlags Flags = EMyPossessFlags::Default);

	UFUNCTION(BlueprintCallable, Category=UPossessLib)
	static void PlayPossessErrorSound(AController* Controller, const FDoPossessProps& Props);

	UFUNCTION(BlueprintCallable, Category=UPossessLib)
	static void PlayPossessSound(AController* Controller, const FDoPossessProps& Props);

	UFUNCTION(BlueprintCallable, Category=UPossessLib)
	static void PlayPossessErrorSound_IfNecessary(AController* Controller, const FDoPossessProps& Props, EMyPossessFlags Flags = EMyPossessFlags::Default);

	UFUNCTION(BlueprintCallable, Category=UPossessLib)
	static void PlayPossessSound_IfNecessary(AController* Controller, const FDoPossessProps& Props, EMyPossessFlags Flags = EMyPossessFlags::Default);
};

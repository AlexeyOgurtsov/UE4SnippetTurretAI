#pragma once

#include "Components/ActorComponent.h"
#include "PossessTypes.h"
#include "PossessControllerComponent.generated.h"

class AController;

UCLASS(ClassGroup=(Possess), meta=(BlueprintSpawnableComponent))
class UPossessControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPossessControllerComponent();


	// ~Initialization Begin
	/**
	* Creates initialized possess controller component using the CreateDefaultSubobject.
	* That's why it's to be used only from the constructor.
	* So, we do NOT expose it to the blueprint.
	*/
	static UPossessControllerComponent* CreateInitializedDefaultSubobject(AController* OwnerController, FName InName);

	/**
	* This function uses the NewObject.
	*/
	UFUNCTION(BlueprintCallable, Category=Possess)
	static UPossessControllerComponent* NewInitializedPossessControllerComponent(AController* OwnerController, FName InName);
	// ~Initialization End

	// ~Possession Begin
	/**
	* Tries to possess actor, check conditions.
	*
	* @returns: true if successfully possessed.
	*/
	UFUNCTION(BlueprintCallable, Category=Possess)
	bool TryPossessActor(AActor* Actor, EMyPossessFlags Flags = EMyPossessFlags::Default);

	/**
	* Whether we may possess actor.
	* Checks all conditions.
	*
	* @returns: true if successfully possessed.
	*/
	UFUNCTION(BlueprintCallable, Category=Possess)
	bool MayPossessActor(AActor* Actor, EMyPossessFlags Flags = EMyPossessFlags::Default);

	/**
	* Tries to possess the given pawn.
	* Checks possession conditions.
	*
	* @returns: true if successfully possessed.
	*/
	UFUNCTION(BlueprintCallable, Category=Possess)
	bool TryPossess(APawn* Pawn, EMyPossessFlags Flags = EMyPossessFlags::Default);

	/**
	* Direct function - just possess the pawn.
	* Never checks whether it may be done according to properties.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Possess)
	void DoRePossess(APawn* Pawn, EMyPossessFlags Flags = EMyPossessFlags::Default);
	virtual void DoRePossess_Implementation(APawn* Pawn, EMyPossessFlags Flags = EMyPossessFlags::Default);

	/**
	* Checks, whether the given pawn may be possessed by the owner controller according to properties.
	* Override in the derived class if you have a custom possess conditions.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Possess)
	bool MayPossessPawn(APawn* Pawn, EMyPossessFlags Flags = EMyPossessFlags::Default) const;
	virtual bool MayPossessPawn_Implementation(APawn* Pawn, EMyPossessFlags Flags = EMyPossessFlags::Default) const;
	// ~Possession End
	
	/**
	* Get the controller we are attached to.
	* Never returns nullptr.
	*/
	UFUNCTION(BlueprintPure)
	AController* GetOwnerController() const;

	/**
	* Get pawn that we're controlling now.
	*/
	UFUNCTION(BlueprintPure, Category = Possess)
	APawn* GetPawn() const;

	/**
	* Pawn to return to.
	* By default this is the first pawn that the controller will possess, but can be overriden.
	*/
	UFUNCTION(BlueprintPure, Category = Possess)
	APawn* GetMainPawn() const { return MainPawn; }

	/**
	* Returns true if current controlled pawn is the main pawn
	*/
	UFUNCTION(BlueprintPure, Category = Possess)
	bool IsMainPawnControlled() const { return GetPawn() == GetMainPawn(); }

	/**
	* Overrides the main pawn.
	*/
	UFUNCTION(BlueprintCallable, Category = Possess)
	void SetMainPawn(APawn* NewPawn);

	/**
	* Helper to switch controller between the main pawn and the given actor (which should be pawn, of course).
	* If current pawn is not main, target does NOT make sense - we always return to the main pawn.
	*/
	UFUNCTION(BlueprintCallable, Category = Possess)
	bool TryTogglePossess(AActor* TargetPawnActor, EMyPossessFlags Flags = EMyPossessFlags::Default);

	/**
	* Helper to possess the main pawn.
	*/
	UFUNCTION(BlueprintCallable, Category = Possess)
	void PossessMainPawn(EMyPossessFlags Flags = EMyPossessFlags::Default);

	// ~Interface for Controller Begin
	/**
	* To be called from controller each time the OnUnPossessed event is called.
	*/
	UFUNCTION(BlueprintCallable)
	void OnController_UnPossessed(APawn* OldPawn);

	/**
	* To be called from controller each time the OnPossessed event is called.
	*/
	UFUNCTION(BlueprintCallable)
	void OnController_Possessed(APawn* OldPawn);
	// ~Interface for Controller End
	
	/** GetPossessProps*/
	UFUNCTION(BlueprintPure, Category=Possess)
	FPossessProps GetPossessProps() const { return PossessProps; }
	
private:
	/**
	* Stack of all pawns in the possession order.
	*/
	UPROPERTY(VisibleInstanceOnly)
	TArray<APawn*> PawnStack;

	UPROPERTY(VisibleInstanceOnly)
	APawn* MainPawn = nullptr;

	/** PossessProps*/
	UPROPERTY(EditAnywhere)
	FPossessProps PossessProps;
};

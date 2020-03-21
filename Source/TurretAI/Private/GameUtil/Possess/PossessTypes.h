#pragma once

#include "PossessTypes.generated.h"

class USoundBase;

UENUM(BlueprintType, Meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor="true"))
enum class EMyPossessFlags : uint8
{
	None = 0 UMETA(DisplayName="None"),

	/**
	* Performs possession ever if the pawn is already posssessed by another pawn
	*/
	PossessEverIfAlreadyControlled = 1 << 0 UMETA(DisplayName="Possess Ever If Already Controlled"),

	/**
	* Provides gameplay feedback (plays sounds etc)
	*/
	GameplayFeedback = 1 << 1 UMETA(DisplayName="GameplayFeedback"),

	Default = PossessEverIfAlreadyControlled | GameplayFeedback UMETA(DisplayName="Default")
};
ENUM_CLASS_FLAGS(EMyPossessFlags);

USTRUCT(BlueprintType)
struct FPossessSounds
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Possess)
	USoundBase* Possessed = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Possess)
	USoundBase* PossessError = nullptr;
};

USTRUCT(BlueprintType)
struct FDoPossessProps
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Possess)
	FPossessSounds Sounds;
};

USTRUCT(BlueprintType)
struct FPossessConditionProps
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Possess)
	float MaxDistance = 1000.0F;
};

USTRUCT(BlueprintType)
struct FPossessProps
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Possess)
	FPossessConditionProps Condition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Possess)
	FDoPossessProps Do;
};

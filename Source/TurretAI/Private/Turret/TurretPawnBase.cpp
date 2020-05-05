#include "TurretPawnBase.h"
#include "TurretBaseConfig.h"
#include "GameUtil/Math/GameMath.h"
#include "Util/TestUtil/I/ITUController.h"
#include "Util/Core/LogUtilLib.h"
#include "Util/Weapon/QuickWeaponComponent/QuickWeaponComponent.h"
#include "Util/Weapon/QuickWeaponComponent/QuickWeaponTypesLib.h"
#include "MyGame/MyPlayerController.h"
#include "Turret/I/TurretEvents.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"

#include "Math/UnrealMathUtility.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"

/**
* TODO:
* 1. Signal when aiming is finished;
* 2. Update when target actor is updated:
*	- Stop aiming when target aim target is destroyed;
*	- update movement aiming direction when aim target changed its location (Should be?)
*/

// WARN
#include "Perception/PawnSensingComponent.h"

#include "PawnBase/MyPawnImpl.h"
#include "Controller/MyAIControllerBase.h"

#include "Engine/CollisionProfile.h"

ATurretPawnBase::ATurretPawnBase()
{
	Impl = UMyPawnImpl::CreateInitialized(this, TEXT("Impl"));
	Events = CreateDefaultSubobject<UTurretEvents>(TEXT("Events"));

	InitMesh(nullptr);
	RootComponent = Mesh;
	{
		RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
		RootSceneComponent->SetupAttachment(Mesh);
	}
	InitProxSphere(RootSceneComponent);

	InitCameraAndSpringArm(RootSceneComponent);
	InitializeSensingComponent();
	InitWeaponComponent();
}

void ATurretPawnBase::InitWeaponComponent()
{
	M_LOGFUNC();
	WeaponComponent = CreateDefaultSubobject<UQuickWeaponComponent>(TEXT("WeaponComponent"));
	UQuickWeaponTypesLib::InitializePrimaryWeapon(WeaponComponent, *GetMesh()->GetName());
}

AMyAIControllerBase* ATurretPawnBase::GetAIControllerBase() const
{
	return Cast<AMyAIControllerBase>(GetController());
}

void ATurretPawnBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TickTurret(DeltaSeconds);
}

void ATurretPawnBase::TickTurret(float DeltaSeconds)
{
	if (TurretState.Aim.TargetActor.IsStale())
	{
		StopAiming(FString(TEXT("TargetActor is stale")), ETurretAimingResult::TargetIsDestroyed);
	}

	TurretState.CurrentTurretYawInComponentSpace = UGameMath::GetUnwindedDegreesUpdatedToTarget(DeltaSeconds, TurretState.CurrentTurretYawInComponentSpace, TurretState.TargetTurretYawInComponentSpace, TurretState.TurretYawUpdate, TurretState.TurretYawUpdateDirection);
	TurretState.CurrentGunPitchInComponentSpace = UGameMath::GetUnwindedDegreesUpdatedToTarget(DeltaSeconds, TurretState.CurrentGunPitchInComponentSpace, TurretState.TargetGunPitchInComponentSpace, TurretState.GunPitchUpdate, TurretState.GunPitchUpdateDirection);
}

void ATurretPawnBase::SignalAimingFinished(ETurretAimingResult InAimResult, AActor* InTargetActor)
{
	Events->OnAimingFinished.Broadcast(FOnTurretAimingFinishedDelegateArgs{InAimResult, InTargetActor});
}

void ATurretPawnBase::BeginPlay()
{
	M_LOGFUNC();
	Super::BeginPlay();
	WeaponComponent->ReAttachToSockets();
	if( GetAIControllerBase() )
	{
		GetAIControllerBase()->OnPawnBeginPlay(this);
	}
}

void ATurretPawnBase::OnController_Axis_LookPitch_Implementation(float InAmount)
{
	// By default, pawn is moving by this controls, as ordinary,
	// so we should call the default controller handlers for movement
	ITUController::Execute_Default_Axis_LookPitch(GetController(), this, InAmount);
}

void ATurretPawnBase::OnController_Axis_LookYaw_Implementation(float InAmount)
{
	// By default, pawn is moving by this controls, as ordinary,
	// so we should call the default controller handlers for movement
	ITUController::Execute_Default_Axis_LookYaw(GetController(), this, InAmount);
}

void ATurretPawnBase::OnController_Axis_Forward_Implementation(float InAmount)
{
	const float DELTA_GUN_PITCH = 10.F;
	RotateGunPitchMinimal(DELTA_GUN_PITCH * InAmount);
}

void ATurretPawnBase::OnController_Axis_Right_Implementation(float InAmount)
{
	const float DELTA_TURRET_YAW = 20.F;
	RotateTurretYawMinimal(DELTA_TURRET_YAW * InAmount);
}

void ATurretPawnBase::OnController_Axis_Up_Implementation(float InAmount)
{
	// By default, pawn is moving by this controls, as ordinary,
	// so we should call the default controller handlers for movement
	ITUController::Execute_Default_Axis_Up(GetController(), this, InAmount);
}

void ATurretPawnBase::OnController_Action_Use_Implementation()
{
	// Unpossession on USE: 
	// It's handled inside the controller's use action handler.
}

void ATurretPawnBase::OnController_Action_UseTwo_Implementation()
{
	// Nothing is to be done here yet
}

void ATurretPawnBase::OnController_Action_UseThree_Implementation()
{
	// Nothing is to be done here yet
}

void ATurretPawnBase::PawnStartFire(uint8 FireModeNum)
{
	// FireModeNum is index of the fire mode (see actions Fire, FireTwo, FireThree)
	// HINT Super::PawnStartFire does nothing in the UE4.24 version!
	Super::PawnStartFire(FireModeNum);
	FireWeaponByIndex_IfCan(FireModeNum);
}

bool ATurretPawnBase::FireWeaponByIndex_IfCan(int32 InWeaponIndex)
{
	if(WeaponComponent == nullptr)
	{
		M_LOG_ERROR(TEXT("Unable to fire: weapon component is nullptr"));
		return false;
	}

	bool bSucceeded = IWeaponInventory::Execute_FireByIndex(WeaponComponent, InWeaponIndex);
	M_LOG_ERROR_IF(bSucceeded, TEXT("Firing failed (index = %d)"), InWeaponIndex);
	return bSucceeded; 
}

UTurretEvents* ATurretPawnBase::K2_GetTurretEvents_Implementation() const
{
	return Events;
}

ETurretAimingResult ATurretPawnBase::K2_StartAimingAt_Implementation(AActor* const NewTargetActor, float AccuracyCoeff)
{	
	bool bShouldStopAiming = false;	

	if (NewTargetActor == nullptr)
	{
		bShouldStopAiming = true;
	}
	else if (NewTargetActor && NewTargetActor != TurretState.Aim.TargetActor)
	{				
		TurretState.Aim.TargetActor = nullptr;
		const ETurretAimingResult AimResult = K2_StartAimingAtPoint_Implementation(NewTargetActor->GetActorLocation(), AccuracyCoeff);
		if (AimResult == ETurretAimingResult::Success || AimResult == ETurretAimingResult::InProgress)
		{
			TurretState.Aim.TargetActor = NewTargetActor;
			return AimResult;
		}
		else
		{
			bShouldStopAiming = true;
		}
	}
	if(bShouldStopAiming)
	{
		StopAiming(FString(TEXT("Stopping aiming")), ETurretAimingResult::Aborted);
	}	
	return ETurretAimingResult::Aborted;
}

ETurretAimingResult ATurretPawnBase::K2_StartAimingAtPoint_Implementation(const FVector& NewTargetPoint, float AccuracyCoeff)
{
	const FVector VectorToTarget = NewTargetPoint - GetActorLocation();

	// @TODO: accuracy calculation
	const FVector2D TargetAzimuthAndElevationDegs = GetPointAzimuthAndElevation(NewTargetPoint, AccuracyCoeff);
	RotateTurretYawMinimalTo(TargetAzimuthAndElevationDegs.X);
	RotateGunPitchMinimalTo(TargetAzimuthAndElevationDegs.Y);

	// @TODO: Check whether target is reachable by distance and azimuth/elevation
	if (!IsTargetReachable(VectorToTarget.Size(), TargetAzimuthAndElevationDegs))
	{
		return ETurretAimingResult::TargetIsUnreachable;
	}

	return ETurretAimingResult::InProgress;
}

FVector2D ATurretPawnBase::K2_GetTargetAzimuthAndElevation_Implementation(AActor* const InTarget, float AccuracyCoeff) const
{	
	checkf(InTarget, TEXT("Target must be NON-nullptr pointer when calling \"%s\""), InTarget);

	return GetPointAzimuthAndElevation(InTarget->GetActorLocation(), AccuracyCoeff);
}

FVector2D ATurretPawnBase::K2_GetPointAzimuthAndElevation_Implementation(const FVector& InTargetPoint, float AccuracyCoeff) const
{
	const FTransform& MeshCompTransform = GetMesh()->GetComponentTransform();

	const FVector CompSpaceTargetLocation = MeshCompTransform.InverseTransformPosition(InTargetPoint);

	const FVector2D TargetAzimuthAndElevation = FMath::GetAzimuthAndElevation
	(
		CompSpaceTargetLocation,
		FVector::ForwardVector,
		FVector::RightVector,
		FVector::UpVector
	);
	const float AzimuthDegs = FMath::RadiansToDegrees(TargetAzimuthAndElevation.X);
	const float ElevationDegs = FMath::RadiansToDegrees(TargetAzimuthAndElevation.Y);
	return FVector2D{ AzimuthDegs, ElevationDegs };
}

bool ATurretPawnBase::K2_IsTargetReachable_Implementation(float const InDistance, const FVector2D& InAzimuthAndElevation) const
{
	if ( ! IsTargetReachableByDistance(InDistance) )
	{
		return false;
	}

	if ( ! IsTargetReachableByElevation(InAzimuthAndElevation))
	{
		return false;
	}

	return true;
}

bool ATurretPawnBase::K2_IsTargetReachableByElevation_Implementation(const FVector2D& InTargetAndElevation) const
{
	return true; // @TODO:
}

bool ATurretPawnBase::K2_IsTargetReachableByDistance_Implementation(float const InDistance) const
{
	return true; // @TODO:	
}

void ATurretPawnBase::K2_StopAiming_Implementation(const FString& InReason, ETurretAimingResult InAimResult)
{
	// @TODO: Stop aiming if we were aiming at target
	if (TurretState.Aim.TargetActor != nullptr)
	{
		M_LOG(TEXT("Stopping to aim; Reason=\"%s\""), *InReason);
		FreezeAimMovement();
		TurretState.Aim.TargetActor = nullptr;
		SignalAimingFinished(InAimResult, nullptr);
	}
}

bool ATurretPawnBase::K2_IsAimingFinished_Implementation() const
{
	return false; // @TODO
}

bool ATurretPawnBase::K2_FireOnce_Implementation(int32 WeaponIndex)
{
	if ( ! CanFireNow(WeaponIndex) )
	{
		return false;
	}
	PawnStartFire(WeaponIndex);
	return true;
}

bool ATurretPawnBase::K2_StartFireFrom_Implementation(int32 WeaponIndex)
{
	return false; // @TODO
}

void ATurretPawnBase::K2_StopFireFrom_Implementation(int32 WeaponIndex)
{
	return; // @TODO
}

bool ATurretPawnBase::K2_CanFireNow_Implementation(int32 WeaponIndex) const
{
	return false; // @TODO
}

void ATurretPawnBase::OnController_Action_Fire_Implementation()
{
	// We process firing inside the PawnStartFire
	PawnStartFire(0);
}

void ATurretPawnBase::OnController_Action_FireTwo_Implementation()
{
	// We process firing inside the PawnStartFire
	PawnStartFire(1);
}

void ATurretPawnBase::OnController_Action_FireThree_Implementation()
{
	// We process firing inside the PawnStartFire
	PawnStartFire(2);
}

void ATurretPawnBase::OnController_Action_DebugOne_Implementation()
{
	if (AMyPlayerController* PC = GetMyPC())
	{
		AActor* const SelectedActor = PC->GetSelectedActor();
		if (SelectedActor)
		{
			const bool bPreviousAimingFinished = IsAimingFinished();
			M_LOG_WARN(TEXT("Aiming at actor \"%s\" of class \"%s\" (Previous aiming finished = \"%s\")"), *SelectedActor->GetName(), *SelectedActor->GetClass()->GetName(), bPreviousAimingFinished ? TEXT("YES") : TEXT("no"));
			const ETurretAimingResult Result = StartAimingAt(SelectedActor);						
			// @TODO: Log aiming result
		}
		else
		{
			M_LOG_WARN(TEXT("Unable to start aiming - No target is selected"));
		}
	}
	else
	{
		M_LOG_ERROR(TEXT("Unable to start aiming - not instance of \"%s\""), *AMyPlayerController::StaticClass()->GetName());
	}
}

AMyPlayerController* ATurretPawnBase::GetMyPC() const
{
	return Cast<AMyPlayerController>(GetController());
}

void ATurretPawnBase::OnController_Action_DebugTwo_Implementation()
{
	// Nothing is to be done here yet
}

void ATurretPawnBase::OnController_Action_DebugThree_Implementation()
{
	// Nothing is to be done here yet
}


TScriptInterface<ITUController> ATurretPawnBase::K2GetTUController() const
{
	return TScriptInterface<ITUController>(GetController());
}

TScriptInterface<ITUController> ATurretPawnBase::K2GetTUControllerLogged(ELogFlags InLogFlags) const
{
	TScriptInterface<ITUController> const C = K2GetTUController();
	if( ! C )
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GetTUController() returned NULL"));
	}
	return C;
}

TScriptInterface<ITUController> ATurretPawnBase::K2GetTUControllerChecked() const
{
	TScriptInterface<ITUController> const C = K2GetTUController();	
	checkf(C, TEXT("GetTUController() must return non-NULL pawn!"));
	return C;
}

ITUController* ATurretPawnBase::GetTUController() const
{
	return Cast<ITUController>(GetController());
}

ITUController* ATurretPawnBase::GetTUControllerLogged(ELogFlags InLogFlags) const
{
	ITUController* const C = GetTUController();
	if(C == nullptr)
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GetTUController() returned NULL"));
	}
	return C;
}

ITUController* ATurretPawnBase::GetTUControllerChecked() const
{
	ITUController* const C = GetTUController();	
	checkf(C, TEXT("GetTUController() must return non-NULL pawn!"));
	return C;
}

AController* ATurretPawnBase::GetControllerLogged(ELogFlags InLogFlags) const
{
	AController* const C = GetController();
	if(C == nullptr)
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GetController() returned NULL"));
	}
	return C;
}

AController* ATurretPawnBase::GetControllerChecked() const
{
	AController* const C = GetController();	
	checkf(C, TEXT("GetController() must return non-NULL pawn!"));
	return C;
}

APlayerController* ATurretPawnBase::GetPCLogged(ELogFlags InLogFlags) const
{
	APlayerController* const C = GetPC();
	if(C == nullptr)
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GetPC() returned NULL"));
	}
	return C;
}

APlayerController* ATurretPawnBase::GetPC() const
{
	return Cast<APlayerController>(GetController());
}

APlayerController* ATurretPawnBase::GetPCChecked() const
{
	APlayerController* const C = GetPC();	
	checkf(C, TEXT("GetController() must return non-NULL pawn!"));
	return C;
}

void ATurretPawnBase::InitCameraAndSpringArm(USceneComponent* InAttachTo)
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = TurretBaseConfig::Default::SPRINGARM_TARGET_ARM_LENGTH;
	SpringArm->SetRelativeRotation(TurretBaseConfig::Default::SPRINGARM_RELATIVE_ROTATION);
	SpringArm->SetRelativeLocation(TurretBaseConfig::Default::SPRINGARM_RELATIVE_LOCATION);
	SpringArm->bEnableCameraLag = TurretBaseConfig::Default::SPRINGARM_ENABLE_CAMERA_LAG;
	SpringArm->CameraLagSpeed = TurretBaseConfig::Default::SPRINGARM_CAMERA_LAG_SPEED;
	if(InAttachTo)
	{
		SpringArm->SetupAttachment(InAttachTo);
	}

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void ATurretPawnBase::InitMesh(USceneComponent* InAttachTo)
{
	static ConstructorHelpers::FObjectFinderOptional<USkeletalMesh> MeshFinder { TurretBaseConfig::Default::MESH_ASSET_PATH };
	M_LOG_ERROR_IF( ! MeshFinder.Succeeded(), TEXT("Default mesh (\"%s\") NOT found"), TurretBaseConfig::Default::MESH_ASSET_PATH);

	{
		Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

		if(MeshFinder.Succeeded())
		{
			M_LOG(TEXT("Default mesh (\"%s\") found, setting it up"), TurretBaseConfig::Default::MESH_ASSET_PATH);
			Mesh->SetSkeletalMesh(MeshFinder.Get(), /*bReInitPose*/true);
			Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			// @TODO: Set default animation blueprint class
			Mesh->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
		}

		if(InAttachTo)
		{
			Mesh->SetupAttachment(InAttachTo);
		}
	}
}

void ATurretPawnBase::InitProxSphere(USceneComponent* InAttachTo)
{
	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	ProxSphere->InitSphereRadius(TurretBaseConfig::Default::PROX_SPHERE_RADIUS);
	ProxSphere->SetRelativeLocation(TurretBaseConfig::Default::MESH_REAL_CENTER_ACTOR_SPACE_LOCATION);
	if(InAttachTo)
	{
		ProxSphere->SetupAttachment(InAttachTo);
	}
}

void ATurretPawnBase::InitializeSensingComponent()	
{
	M_LOGFUNC();
	Sensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("SensingComponent"));
	Sensing->OnSeePawn.AddDynamic(this, &ATurretPawnBase::OnSeePawn);
}
// ~ AActor Begin
float ATurretPawnBase::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return Impl->TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}
// ~ AActor End

// ~ IMyPawnBase Begin
FMyHitState ATurretPawnBase::GetHitState_Implementation() const
{
	return Impl->HitState;
}

UMyPawnEvents* ATurretPawnBase::GetEvents_Implementation() const
{
	return Impl->MyEvents;
}
UPawnSensingComponent* ATurretPawnBase::GetSensingComponent_Implementation() const
{
	return Sensing;
}
void ATurretPawnBase::OnSeePawn(APawn* InPawn)
{
	// Nothing is to be done here yet
}
// ~ IMyPawnBase End

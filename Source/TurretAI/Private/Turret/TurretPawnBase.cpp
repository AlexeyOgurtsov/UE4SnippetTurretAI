#include "TurretPawnBase.h"
#include "TurretBaseConfig.h"
#include "GameUtil/Math/GameMath.h"
#include "Util/TestUtil/I/ITUController.h"
#include "Util/Core/LogUtilLib.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"

#include "UObject/ConstructorHelpers.h"

#include "Components/SkeletalMeshComponent.h"

// WARN
#include "Perception/PawnSensingComponent.h"

#include "PawnBase/MyPawnImpl.h"
#include "Controller/MyAIControllerBase.h"

#include "Engine/CollisionProfile.h"

ATurretPawnBase::ATurretPawnBase()
{
	Impl = UMyPawnImpl::CreateInitialized(this, TEXT("Impl"));

	InitMesh(nullptr);
	RootComponent = Mesh;
	{
		RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
		RootSceneComponent->SetupAttachment(Mesh);
	}
	InitProxSphere(RootSceneComponent);

	InitCameraAndSpringArm(RootSceneComponent);
	InitializeSensingComponent();
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
	TurretState.CurrentTurretYawInComponentSpace = UGameMath::GetUnwindedDegreesUpdatedToTarget(DeltaSeconds, TurretState.CurrentTurretYawInComponentSpace, TurretState.TargetTurretYawInComponentSpace, TurretState.TurretYawUpdate, TurretState.TurretYawUpdateDirection);
	TurretState.CurrentGunPitchInComponentSpace = UGameMath::GetUnwindedDegreesUpdatedToTarget(DeltaSeconds, TurretState.CurrentGunPitchInComponentSpace, TurretState.TargetGunPitchInComponentSpace, TurretState.GunPitchUpdate, TurretState.GunPitchUpdateDirection);
}

void ATurretPawnBase::BeginPlay()
{
	M_LOGFUNC();
	Super::BeginPlay();
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
	// By default, pawn is moving by this controls, as ordinary,
	// so we should call the default controller handlers for movement
	ITUController::Execute_Default_Axis_Forward(GetController(), this, InAmount);
}

void ATurretPawnBase::OnController_Axis_Right_Implementation(float InAmount)
{
	// By default, pawn is moving by this controls, as ordinary,
	// so we should call the default controller handlers for movement
	ITUController::Execute_Default_Axis_Right(GetController(), this, InAmount);
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
	// @TODO: Typically here implement the real firing!
}

void ATurretPawnBase::OnController_Action_Fire_Implementation()
{
	// We process firing inside the PawnStartFire
}

void ATurretPawnBase::OnController_Action_FireTwo_Implementation()
{
	// We process firing inside the PawnStartFire
}

void ATurretPawnBase::OnController_Action_FireThree_Implementation()
{
	// We process firing inside the PawnStartFire
}

void ATurretPawnBase::OnController_Action_DebugOne_Implementation()
{
	// Nothing is to be done here yet
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

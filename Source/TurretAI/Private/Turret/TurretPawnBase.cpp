#include "TurretPawnBase.h"
#include "TurretBaseConfig.h"
#include "GameUtil/Math/GameMath.h"
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

ATurretPawnBase::ATurretPawnBase()
{
	Impl = UMyPawnImpl::CreateInitialized(this, TEXT("Impl"));

	InitProxSphere(RootSceneComponent);
	RootComponent = ProxSphere;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootSceneComponent->SetupAttachment(RootComponent);

	InitCameraAndSpringArm(RootSceneComponent);
	InitMesh(RootSceneComponent);

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

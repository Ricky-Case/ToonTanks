#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	moveSpeed *= moveSpeedModifier;
	turnSpeed *= turnSpeedModifier;

	PlayerController = Cast<APlayerController>(GetController());
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PlayerController)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult);

		RotateTurret(HitResult.ImpactPoint, DeltaTime);
	}
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

APlayerController* ATank::GetPlayerController() const { return PlayerController; }

void ATank::Move(float scalar)
{
	AddActorLocalOffset(
		FVector(scalar, 0.0, 0.0) * moveSpeed * TimeScale(),
		true
	);
}

void ATank::Turn(float scalar)
{
	if(GetInputAxisValue(TEXT("MoveForward")) < 0.0f)
	{
		AddActorLocalRotation(
			FRotator(0.0, -scalar, 0.0) * turnSpeed * TimeScale()
		);
	}
	else
	{
		AddActorLocalRotation(
			FRotator(0.0, scalar, 0.0) * turnSpeed * TimeScale()
		);
	}
}

float ATank::TimeScale() { return UGameplayStatics::GetWorldDeltaSeconds(this); }
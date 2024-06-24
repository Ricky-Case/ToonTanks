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

	TankPlayerController = Cast<APlayerController>(GetController());
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

	if(TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult);
		
		DrawDebugSphere(
			GetWorld(),
			HitResult.ImpactPoint,
			25.0f,
			8,
			FColor::Green,
			false,
			-1.0f
		);

		RotateTurret(HitResult.ImpactPoint, DeltaTime);
	}
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

APlayerController* ATank::GetPlayerController() const
{
	return TankPlayerController;
}

void ATank::Move(float scalar)
{
	AddActorLocalOffset(
		FVector(scalar, 0.0, 0.0) * moveSpeed * TimeScale(),
		true
	);
}

void ATank::Turn(float scalar)
{
	AddActorLocalRotation(
		FRotator(0.0, scalar, 0.0) * turnSpeed * TimeScale()
	);
}

float ATank::TimeScale() { return UGameplayStatics::GetWorldDeltaSeconds(this); }
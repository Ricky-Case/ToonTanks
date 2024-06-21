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

	PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PlayerControllerRef)
	{
		FHitResult HitResult;
		PlayerControllerRef->GetHitResultUnderCursor(
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

void ATank::Move(float scalar)
{
	if(scalar != 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Movement Scalar Value: %f"), scalar);
		
		float timeScale = UGameplayStatics::GetWorldDeltaSeconds(this); // Using DeltaTime to regulate speed
		AddActorLocalOffset(
			FVector(scalar, 0.0, 0.0) * moveSpeed * timeScale,
			true
		);
	}
}

void ATank::Turn(float scalar)
{
	if(scalar != 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Scalar Value: %f"), scalar);

		float timeScale = UGameplayStatics::GetWorldDeltaSeconds(this); // Using DeltaTime to regulate speed
		AddActorLocalRotation(FRotator(0.0, scalar, 0.0) * turnSpeed * timeScale);
	}
}
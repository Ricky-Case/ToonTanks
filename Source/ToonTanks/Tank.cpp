#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
	moveSpeed *= 100;
	turnSpeed *= 25;
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

void ATank::Move(float scalar)
{
	if(scalar != 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Scalar Value: %f"), scalar);
		
		AddActorLocalOffset(FVector(scalar, 0.0, 0.0) * moveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this)); // Using DeltaTime to regulate speed
	}
}

void ATank::Turn(float scalar)
{
	if(scalar != 0.0f) { UE_LOG(LogTemp, Warning, TEXT("Scalar Value: %f"), scalar); }
	AddActorLocalRotation(FRotator(0.0, scalar, 0.0) * turnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this)); // Using DeltaTime to regulate speed
}
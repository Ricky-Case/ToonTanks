#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Projectile.h"

ABasePawn::ABasePawn()
{
 	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = Capsule;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(Capsule);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawn->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	if(ExplosionParticles) { UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionParticles, GetActorLocation(), GetActorRotation()); }
	
	if(DeathSound) { UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation()); }
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

	rotateTurretSpeed *= rotateTurretSpeedMod;
}

void ABasePawn::RotateTurret(FVector TargetLocation, float DeltaTime)
{
	FVector ToTarget = TargetLocation - TurretMesh->GetComponentLocation();
	FRotator LookRotation = FRotator(0.0f, ToTarget.Rotation().Yaw, 0.0f);
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			LookRotation,
			DeltaTime,
			rotateTurretSpeed
		)
	);
}

void ABasePawn::Fire()
{
	auto projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileClass,
		ProjectileSpawn->GetComponentLocation(),
		ProjectileSpawn->GetComponentRotation()
	);

	projectile->SetOwner(this);
}
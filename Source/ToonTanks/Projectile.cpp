// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AProjectile::AProjectile()
{
 	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = initialVelocity;
	ProjectileMovementComponent->MaxSpeed = maxVelocity;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Soke Trail"));
	TrailParticles->SetupAttachment(RootComponent);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if(LaunchSound) { UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation()); }
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto owner = GetOwner();
	if(owner && OtherActor && (OtherActor != this) && (OtherActor != owner))
	{
		UGameplayStatics::ApplyDamage(OtherActor, damage, owner->GetInstigatorController(), this, UDamageType::StaticClass());
		if(HitParticles) { UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation()); }

		if(HitSound) { UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation()); }
	}

	Destroy();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
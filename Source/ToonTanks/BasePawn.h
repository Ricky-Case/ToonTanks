#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class AProjectile;
class UCapsuleComponent;
class UParticleSystem;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();

	void HandleDestruction();

protected:
	virtual void BeginPlay() override;
	void RotateTurret(FVector TargetLocation, float DeltaTime);
	void Fire();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* Capsule;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawn;
	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem* ExplosionParticles;
	UPROPERTY(EditAnywhere, Category = "Player Control")
	float rotateTurretSpeed = 10.0f;
	UPROPERTY(EditAnywhere, Category = "Player Control")
	float rotateTurretSpeedMod = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* DeathSound;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<AProjectile> ProjectileClass;
};
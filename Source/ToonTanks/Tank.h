#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	void Move(float scalar);
	void Turn(float scalar);
	void Rotate(float scalar);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Player Control")
	float moveSpeed = 10;

	UPROPERTY(EditAnywhere, Category = "Player Control")
	float turnSpeed = 10;

	UPROPERTY(EditAnywhere, Category = "Player Control")
	int32 moveSpeedModifier = 10;

	UPROPERTY(EditAnywhere, Category = "Player Control")
	float turnSpeedModifier = 2.5;

	APlayerController* PlayerControllerRef;
};

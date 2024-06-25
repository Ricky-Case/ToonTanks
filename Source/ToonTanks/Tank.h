#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();
	APlayerController* GetPlayerController() const;

	bool bAlive = true;

protected:
	virtual void BeginPlay() override;

private:
	void Move(float scalar);
	void Turn(float scalar);
	void Rotate(float scalar);
	float TimeScale();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Player Control")
	float moveSpeed = 10.0f;
	UPROPERTY(EditAnywhere, Category = "Player Control")
	float moveSpeedModifier = 10;
	UPROPERTY(EditAnywhere, Category = "Player Control")
	float turnSpeed = 10.0f;
	UPROPERTY(EditAnywhere, Category = "Player Control")
	float turnSpeedModifier = 2.5;

	APlayerController* PlayerController;
};

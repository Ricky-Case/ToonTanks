// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
private:
	void CheckFireCondition();
	bool InFireRange();

	class ATank* Tank;

	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditAnywhere, Category = "AI Control")
	float fireRange = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "AI Control")
	float fireRate = 2.0f;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(InFireRange()) { RotateTurret(Tank->GetActorLocation(), DeltaTime); }

}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(
		FireRateTimerHandle,
		this,
		&ATower::CheckFireCondition,
		fireRate,
		true
		);
}

void ATower::CheckFireCondition()
{
	if(Tank)
	{
		if(InFireRange() && Tank->bAlive) { Fire(); }
	}
}

bool ATower::InFireRange()
{
	if(Tank)
	{
		float distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if(distance <= fireRange) { return true; }
	}

	return false;
}
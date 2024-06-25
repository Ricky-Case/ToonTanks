#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if(DeadActor == Tank)
	{
		Tank->HandleDestruction();

		if(ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}

		GameOver(false);
	}
	else if(ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();

		if(--towerCount <= 0) { GameOver(true); }
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();

}

void AToonTanksGameMode::HandleGameStart()
{
	towerCount = GetTowerCount();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if(ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true
		);

		GetWorldTimerManager().SetTimer(
			PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			startDelay,
			false
		);
	}
}

int32 AToonTanksGameMode::GetTowerCount() const
{
	TArray<AActor*> towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), towers);

	return towers.Num();
}
#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if(DeadActor == Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TANK DESTROYED!"));
		Tank->HandleDestruction();

		if(ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
	}
	else if(ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("TOWER DESTROYED!"));
		DestroyedTower->HandleDestruction();
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}
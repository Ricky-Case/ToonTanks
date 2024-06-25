#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	void HandleGameStart();
	int32 GetTowerCount() const;

	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;
	int32 towerCount = 0;

	UPROPERTY(EditAnywhere)
	float startDelay = 3.0f;
};

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

private:
	void HandleGameStart();

	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;

	UPROPERTY(EditAnywhere)
	float startDelay = 3.0f;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	health = maxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
}


void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
	if(Damage > 0.0f && health > 0.0f)
	{
		UE_LOG(LogTemp, Error, TEXT("%f DAMAGE TAKEN BY %s!"), Damage, *GetOwner()->GetName());

		health -= Damage;
		if(health < 0.0f) { health -= health; }

		UE_LOG(LogTemp, Warning, TEXT("HEALTH: %f"), health);
	}
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


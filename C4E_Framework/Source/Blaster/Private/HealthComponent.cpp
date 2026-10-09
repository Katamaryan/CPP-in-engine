// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"


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

	// ...
	
}

void UHealthComponent::ResetHealth_Implementation()
{
	CurrentHealth = MaxHealth;
	bIsDead = false;
	bIsInvulnerable = false;
	//TODO EventDispatcher goes here
}

void UHealthComponent::CheckDeath_Implementation(AController* Instigator, AActor* Causer)
{
	if (CurrentHealth <= 0)
	{
		bIsDead = true;
	}
	//TODO EventDispatcher goes here later
}

float UHealthComponent::GetCurrentHealth_Implementation()
{
	return CurrentHealth;
}

bool UHealthComponent::IsDead_Implementation()
{
	return bIsDead;
}




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

	//gets the owner of the health component, binds to the OnTakeAnyDamage event dispatcher,
	//and calls the applyDamage function as a listener to the dispatcher as a unique listener
	GetOwner()->OnTakeAnyDamage.AddUniqueDynamic(this, &UHealthComponent::ApplyDamage);
	
}

void UHealthComponent::ApplyDamage_Implementation(AActor* DamagedActor, float Damage,
	const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if ( bIsDead || bIsInvulnerable )
	{
		return;
	}
	else
	{
		CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);
		OnHealthModified.Broadcast(Damage > 0.0f, CurrentHealth, Damage, CurrentHealth / MaxHealth);
		CheckDeath_Implementation(InstigatedBy, DamageCauser);
	}
}

void UHealthComponent::ResetHealth_Implementation()
{
	CurrentHealth = MaxHealth;
	bIsDead = false;
	bIsInvulnerable = false;
	OnHealthModified.Broadcast(false, CurrentHealth, 0.0f, CurrentHealth / MaxHealth);
}

void UHealthComponent::CheckDeath_Implementation(AController* Instigator, AActor* Causer)
{
	if (CurrentHealth <= 0.0f)
	{
		bIsDead = true;
		OnDeath.Broadcast(Instigator, Causer);
	}
}

float UHealthComponent::GetCurrentHealth_Implementation()
{
	return CurrentHealth;
}

bool UHealthComponent::IsDead_Implementation()
{
	return bIsDead;
}




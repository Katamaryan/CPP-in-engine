// Fill out your copyright notice in the Description page of Project Settings.


#include "EncounterManager.h"


// Sets default values
AEncounterManager::AEncounterManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEncounterManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEncounterManager::EncounterCompleted_Implementation()
{
}

void AEncounterManager::OnTargetDestroyed_Implementation()
{
}

void AEncounterManager::OnEncounterTriggered_Implementation(UPrimitiveComponent* OverlappedComponent,
                                                            AActor* OtherActor)
{
}




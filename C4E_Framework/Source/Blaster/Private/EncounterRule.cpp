// Fill out your copyright notice in the Description page of Project Settings.


#include "EncounterRule.h"

#include "EncounterManager.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UEncounterRule::UEncounterRule()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEncounterRule::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UEncounterRule::InitRule(int ID)
{
	Super::InitRule(ID);
	
	EncounterManager = Cast<AEncounterManager>(UGameplayStatics::GetActorOfClass(this, AEncounterManager::StaticClass()));
	EncounterManager->OnEncountersCompleted.AddDynamic(this, &UEncounterRule::CompleteRule);
}

void UEncounterRule::CompleteRule()
{
	Completed = true;
	OnRuleCompleted.Broadcast(RuleID, Completed);
}








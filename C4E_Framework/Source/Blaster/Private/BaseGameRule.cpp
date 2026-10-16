// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameRule.h"


// Sets default values for this component's properties
UBaseGameRule::UBaseGameRule()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBaseGameRule::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UBaseGameRule::CompleteRule_Implementation()
{
	OnRuleCompleted.Broadcast(RuleID, Completed);
}

void UBaseGameRule::UpdateRuleConditions_Implementation()
{
	
}

void UBaseGameRule::InitRule_Implementation(int ID)
{
	RuleID = ID;
}





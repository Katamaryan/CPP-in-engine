// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerGameRule.h"


// Sets default values for this component's properties
UTimerGameRule::UTimerGameRule()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTimerGameRule::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTimerGameRule::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTimerGameRule::InitRule(int ID)
{
	Super::InitRule_Implementation(ID);
	
	GetWorld()->GetTimerManager().SetTimer(Timer,this, &UTimerGameRule::TimerEnded_Implementation, TimerLength);
	
	GetWorld()->GetTimerManager().SetTimer(TimerCheckTimer,this, &UTimerGameRule::TimerCheck_Implementation, 1.0f, true);
	
	OnTimerStarted.Broadcast();
}

void UTimerGameRule::DeductFromTimer_Implementation(float SecondsToRemove)
{
	float TimeRemaining = GetWorld()->GetTimerManager().GetTimerRemaining(TimerCheckTimer);
	if ( TimeRemaining > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UTimerGameRule::TimerEnded_Implementation, TimeRemaining - SecondsToRemove);
	}
}

void UTimerGameRule::AddToTimer_Implementation(float SecondsToAdd)
{
	float TimeRemaining = GetWorld()->GetTimerManager().GetTimerRemaining(Timer);
	if (TimeRemaining > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UTimerGameRule::TimerEnded_Implementation, TimeRemaining + SecondsToAdd);
	}
}

void UTimerGameRule::TimerEnded_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerCheckTimer);
	OnTimerCompleted.Broadcast();
	Completed = true;
	CompleteRule();
}

void UTimerGameRule::TimerCheck_Implementation()
{
	float TimeRemaining = GetWorld()->GetTimerManager().GetTimerRemaining(Timer);
	if (TimeRemaining > 0.0f)
	{
		OnTimerTicked.Broadcast(TimeRemaining);
	}
}


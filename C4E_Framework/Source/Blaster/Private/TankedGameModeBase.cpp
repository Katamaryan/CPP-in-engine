// Fill out your copyright notice in the Description page of Project Settings.


#include "TankedGameModeBase.h"
#include "BaseGameRule.h"
#include "Kismet/KismetSystemLibrary.h"

void ATankedGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	RegisterGameRules();
	
	if (ActiveRules.IsEmpty())
		return;
	
	for ( int i = 0; i < ActiveRules.Num(); i++ )
	{
		ActiveRules[i]->InitRule(i);
		ActiveRules[i]->OnRuleCompleted.AddUniqueDynamic(this, &ATankedGameModeBase::OnRuleCompleted);
	}
	
	CreateUIElementsForRules();
}

void ATankedGameModeBase::OnEndTimerComplete_Implementation()
{
	GetWorldTimerManager().ClearTimer(EndGameTimerHandle);
	
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}

void ATankedGameModeBase::CreateUIElementsForRules_Implementation()
{
}

void ATankedGameModeBase::OnRuleCompleted_Implementation(int ruleID, bool successful)
{
	
	if (CheckRules_Implementation(ruleID, successful))
		EndGame_Implementation();
}

void ATankedGameModeBase::EndGame_Implementation()
{
	GetWorldTimerManager().SetTimer(EndGameTimerHandle, this, &ATankedGameModeBase::OnEndTimerComplete, 1.0f, false );
	
}

void ATankedGameModeBase::RegisterGameRules_Implementation()
{
}

bool ATankedGameModeBase::CheckRules_Implementation(int ruleID, bool successful)
{
	if (successful)
	{
		
		if (ActiveRules[ruleID]->MajorRule)
		{
			return true;
		}
		for ( int i = 0; i < ActiveRules.Num(); i++)
		{
			if (!ActiveRules[i]->Completed)
				return false;
		}
		return true;
	}
	return false;
}


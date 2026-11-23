// Fill out your copyright notice in the Description page of Project Settings.


#include "EncountersUIWidget.h"

#include "EncounterManager.h"
#include "Kismet/GameplayStatics.h"

void UEncountersUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	EncounterManager = Cast<AEncounterManager>(UGameplayStatics::GetActorOfClass(this, AEncounterManager::StaticClass()));

	if (IsValid(EncounterManager))
	{
		EncounterManager->OnEncounterStarted.AddDynamic(this, &UEncountersUIWidget::OnEncounterStarted);
		EncounterManager->OnEncounterEnded.AddDynamic(this, &UEncountersUIWidget::OnEncounterEnded);
		EncounterManager->OnTargetCountUpdated.AddDynamic(this, &UEncountersUIWidget::OnTargetCountUpdated);
	}
}

void UEncountersUIWidget::OnEncounterStarted_Implementation(int TotalTargetsParameter)
{
	TotalTargets = TotalTargetsParameter;
	
	//T_Encounters = FText::Format(NSLOCTEXT("Encounter:" "{0}/{1}"), (FText::AsNumber(TotalTargetsParameter), FText::AsNumber(TotalTargets)));
}

void UEncountersUIWidget::OnTargetCountUpdated_Implementation(int TotalCount)
{
}

void UEncountersUIWidget::OnEncounterEnded_Implementation()
{
}

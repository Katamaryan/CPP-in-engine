// Fill out your copyright notice in the Description page of Project Settings.


#include "EncountersUIWidget.h"

#include "EncounterManager.h"
#include "Components/TextBlock.h"
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

void UEncountersUIWidget::SetVisibilityCollapsed_Implementation()
{
	TEncounters->SetVisibility(ESlateVisibility::Collapsed);
}

void UEncountersUIWidget::OnEncounterStarted_Implementation(int TotalTargetsParameter)
{
	TotalTargets = TotalTargetsParameter;
	TEncounters->SetText(FText::FromString(FString::Printf(TEXT("Encounter: %d/%d"), TotalTargets,TotalTargetsParameter)));
	TEncounters->SetVisibility(ESlateVisibility::Visible);
}

void UEncountersUIWidget::OnTargetCountUpdated_Implementation(int TotalCount)
{
	TEncounters->SetText(FText::FromString(FString::Printf(TEXT("Encounter: %d/%d"), TotalCount,TotalTargets)));
	
}

void UEncountersUIWidget::OnEncounterEnded_Implementation()
{
	TEncounters->SetText(FText::FromString(FString::Printf(TEXT("Encounter Completed!"))));
	GetWorld()->GetTimerManager().SetTimer(DelayTimer, this, &UEncountersUIWidget::SetVisibilityCollapsed_Implementation, 1.0f);
}

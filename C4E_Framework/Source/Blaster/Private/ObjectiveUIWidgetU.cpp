// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveUIWidgetU.h"

#include "BaseGameRule.h"
#include "Components/PanelWidget.h"
#include "Kismet/GameplayStatics.h"

void UObjectiveUIWidgetU::InitRules(TArray<UBaseGameRule*> Rules)
{
	for ( int i = 0; i< Rules.Num(); i++)
	{
		if (UKismetSystemLibrary::IsValidClass(Rules[i]->RuleUI))
		{
			ObjectivesPanel->AddChild(CreateWidget<UUserWidget, UObjectiveUIWidgetU*>(this, Rules[i]->RuleUI.Get()));
		}
	}
}


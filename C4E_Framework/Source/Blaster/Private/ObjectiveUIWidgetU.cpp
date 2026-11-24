// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveUIWidgetU.h"

#include "BaseGameRule.h"
#include "Kismet/GameplayStatics.h"

void UObjectiveUIWidgetU::InitRules_Implementation(TArray<TObjectPtr<UBaseGameRule>> ActiveRules)
{
	for ( int i = 0; i< ActiveRules.Num(); i++)
	{
		if (UKismetSystemLibrary::IsValidClass(ActiveRules[i]->RuleUI))
		{
			//CreateWidget<ActiveRules[i]->RuleUI>(nullptr, ActiveRules[i]->RuleUI->GetClass()::StaticClass<>());
		}
	}
}

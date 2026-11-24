// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveUIWidgetU.generated.h"

class UBaseGameRule;
/**
 * 
 */
UCLASS(ABSTRACT)
class BLASTER_API UObjectiveUIWidgetU : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UPanelWidget> ObjectivesPanel;
	
public:
	
	
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent )
	void InitRules(TArray<TObjectPtr<UBaseGameRule>> ActiveRules );
};

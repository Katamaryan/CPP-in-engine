// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "EncountersUIWidget.generated.h"

class AEncounterManager;
class UTextBlock;
/**
 * 
 */
UCLASS()
class BLASTER_API UEncountersUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> T_Encounters;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TotalTargets;
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AEncounterManager> EncounterManager;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnEncounterStarted(int TotalTargetsParameter);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnTargetCountUpdated(int TotalCount);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnEncounterEnded();
	
};

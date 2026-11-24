// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerUIWidget.generated.h"

class UTimerGameRule;
class UTextBlock;
/**
 * 
 */
UCLASS()
class BLASTER_API UTimerUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> T_Timer;

	virtual void NativeConstruct() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTimerGameRule> TimerRule;
	int Totaltargets;
	
	UFUNCTION(BlueprintCallable, blueprintNativeEvent)
	void OnTimerStarted();
	UFUNCTION(BlueprintCallable, blueprintNativeEvent)
	void OnTimerTicked(float TimeRemaining);
	UFUNCTION(BlueprintCallable, blueprintNativeEvent)
	void OnTimerEnded();
	UFUNCTION(BlueprintCallable, blueprintNativeEvent)
	void UpdateText(float Seconds);
};

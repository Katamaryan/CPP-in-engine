// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUIWidget.generated.h"

class ATank;
class UProgressBar;
/**
 * 
 */
UCLASS(ABSTRACT)
class BLASTER_API UMainUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TotalTargets;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ATank> TankREF;
	
	UFUNCTION(BlueprintCallable)
	void UpdateHealthBar(float newHeatlthRatio);
};

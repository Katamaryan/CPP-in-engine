// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndReachedUIWidget.generated.h"

class UTextBlock;
class AEndPoint;
/**
 * 
 */
UCLASS(ABSTRACT)
class BLASTER_API UEndReachedUIWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> T_Escape;
	virtual void NativeConstruct() override;
	
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<AEndPoint> EndPoint;
	int TotalTargets;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnEndActivated();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankedGameModeBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BLASTER_API ATankedGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UBaseGameRule>> ActiveRules;
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnRuleCompleted(int ruleID, bool successful);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EndGame();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RegisterGameRules();
	
	UFUNCTION(Blueprintcallable, BlueprintNativeEvent)
	bool CheckRules(int ruleID, bool successful);
	
};


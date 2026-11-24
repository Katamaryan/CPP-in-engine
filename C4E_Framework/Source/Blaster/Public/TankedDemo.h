// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankedGameModeBase.h"
#include "TankedDemo.generated.h"

class UEncounterRule;
class UEndReachedRule;
class UTimerGameRule;
/**
 * 
 */
UCLASS()
class BLASTER_API ATankedDemo : public ATankedGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void RegisterGameRules_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTimerGameRule> TimerGameRule;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UEndReachedRule> EndReachedRule;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UEncounterRule> EncounterRule;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameRule.h"
#include "EncounterRule.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLASTER_API UEncounterRule : public UBaseGameRule
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEncounterRule();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

};

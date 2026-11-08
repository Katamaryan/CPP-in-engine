// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructs.generated.h"

USTRUCT(BlueprintType)
struct FEncounter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EncounterID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<AActor>> EncounterActors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bStartSpawned;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<AActor>> StartInteractors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<AActor>> EndInteractors;
	
};
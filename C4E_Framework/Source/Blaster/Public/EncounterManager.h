// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructs.h"
#include "GameFramework/Actor.h"
#include "EncounterManager.generated.h"

UCLASS()
class BLASTER_API AEncounterManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEncounterManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEncounter> LevelEncounters;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentTargetCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> CompletedEncounters;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEncounter TargetEncounter;
	
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnEncounterTriggered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnTargetDestroyed();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EncounterCompleted();
};

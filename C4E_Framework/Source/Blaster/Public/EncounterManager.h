// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructs.h"
#include "GameFramework/Actor.h"
#include "EncounterManager.generated.h"

class ATank;
class ATriggerBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEncounterStartedSignature, int, TotalTargets);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetCountUpdatedSignature, int, TargetCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEncounterEndedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEncountersCompletedSignature);

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ATriggerBase*, int> EncounterTriggers;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ATriggerBase*> Encounters; 
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnEncounterTriggered(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnTargetDestroyed();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EncounterCompleted();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ActivateEncounter(int EncounterID);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DisableTarget(AActor* TargetActor);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EnableTarget(AActor* TargetActor);
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FEncounterStartedSignature OnEncounterStarted;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FTargetCountUpdatedSignature OnTargetCountUpdated;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FEncounterEndedSignature OnEncounterEnded;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FEncountersCompletedSignature OnEncountersCompleted;
};

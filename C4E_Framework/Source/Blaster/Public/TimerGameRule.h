// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameRule.h"
#include "TimerGameRule.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerStartedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerTickedSignature, float, TimerRemaining);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerCompletedSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLASTER_API UTimerGameRule : public UBaseGameRule
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTimerGameRule();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimerLength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle Timer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle TimerCheckTimer;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void InitRule(int ID) ;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TimerCheck();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TimerEnded();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddToTimer(float SecondsToAdd);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DeductFromTimer(float SecondsToRemove);
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnTimerStartedSignature OnTimerStarted;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnTimerTickedSignature OnTimerTicked;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnTimerCompletedSignature OnTimerCompleted;
};

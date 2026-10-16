// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseGameRule.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuleCompletedSignature, int, RuleID, bool, bSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRuleUpdatedSignatre);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLASTER_API UBaseGameRule : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBaseGameRule();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RuleID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Completed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool MajorRule;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> RuleUI;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InitRule(int ID);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateRuleConditions();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CompleteRule();
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FRuleCompletedSignature OnRuleCompleted;
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FRuleUpdatedSignatre OnRuleUpdated;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameRule.h"
#include "EndReachedRule.generated.h"


class AEndPoint;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLASTER_API UEndReachedRule : public UBaseGameRule
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEndReachedRule();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AEndPoint> EndPoint;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void InitRule(int ID) override;
	
	UFUNCTION(BlueprintCallable, BLueprintNativeEvent)
	void OnEndReached();
};

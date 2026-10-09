// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLASTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	bool bIsDead = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	bool bIsInvulnerable = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float CurrentHealth = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float MaxHealth;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsDead();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetCurrentHealth();
	UFUNCTION(BlueprintCallable, blueprintNativeEvent)
	void CheckDeath(AController* Instigator, AActor* Causer);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ResetHealth();
};

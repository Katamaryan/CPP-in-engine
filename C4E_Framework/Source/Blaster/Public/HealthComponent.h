// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FHealthModifiedSignature, bool, bPositive, float, NewHealth, float, HealthDelta, float, HealthRatio);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDeathSignature, AController*, Instigator, AActor*, Causer);

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
	//define variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	bool bIsDead = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	bool bIsInvulnerable = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float CurrentHealth = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float MaxHealth;
	
	//define functions
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsDead();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetCurrentHealth();
	UFUNCTION(BlueprintCallable, blueprintNativeEvent)
	void CheckDeath(AController* Instigator, AActor* Causer);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ResetHealth();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ApplyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	//Define Delegates
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FHealthModifiedSignature OnHealthModified;
	UPROPERTY(BlueprintCallable, blueprintassignable)
	FDeathSignature OnDeath;
};

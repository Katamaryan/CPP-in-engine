// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyFirstActor.generated.h"

class UBoxComponent;

UCLASS(Abstract)
class BLASTER_API AMyFirstActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyFirstActor();

	
	UPROPERTY(EditAnywhere);
	TObjectPtr<UBoxComponent> _collider;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> _staticMesh;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> _explosion;
	
	UPROPERTY(EditAnywhere)
	FTimerHandle _timer;
	
	UFUNCTION(BlueprintCallable)
	void HandleDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
	UFUNCTION(blueprintCallable)
	void BlowUp();
	
	virtual void BeginPlay() override;
};

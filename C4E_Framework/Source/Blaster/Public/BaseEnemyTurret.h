// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "BaseEnemyTurret.generated.h"

class UTargetComponent;
class UTimelineComponent;
class ATank;
class UHealthComponent;
class UBoxComponent;
class UParticleSystem;

UCLASS(ABSTRACT)
class BLASTER_API ABaseEnemyTurret : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseEnemyTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> _box;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UStaticMeshComponent>> _staticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UParticleSystem> EnemyDeath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTargetComponent> _target;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* TankREF;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle FireRateHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTimelineComponent> TurretRecoil ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCurveFloat> RecoilCurve ;
	FOnTimelineFloat OnTurretUpdate;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TurretDestroyed(AController* InstigatedBy, AActor* Causer);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Fire();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TurretGunShake(float value);
	
	UFUNCTION(BlueprintCallable)
	virtual void TurretFire();
	
};

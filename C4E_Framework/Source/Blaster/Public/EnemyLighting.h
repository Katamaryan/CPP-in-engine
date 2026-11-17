// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemyTurret.h"
#include "EnemyLighting.generated.h"

UCLASS()
class BLASTER_API AEnemyLighting : public ABaseEnemyTurret
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyLighting();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UStaticMeshComponent>> _rig;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UParticleSystemComponent>> _lightningCharge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCurveFloat> FireCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCurveFloat> FXBuildupCurve;
	FOnTimelineFloat OnTurretFXBuildup;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

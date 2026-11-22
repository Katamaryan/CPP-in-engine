// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemyTurret.h"
#include "EnemyRocket.generated.h"

class ARocket;
class UArrowComponent;

UCLASS(ABSTRACT)
class BLASTER_API AEnemyRocket : public ABaseEnemyTurret
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyRocket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UStaticMeshComponent>> _rig;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UStaticMeshComponent>> _turretPod;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UArrowComponent>> _arrow;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTimelineComponent> RocketShake;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCurveFloat> RocketCurve;
	FOnTimelineFloat OnRocketUpdate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ARocket> _rocket;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPoint;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void TurretFire() override;
	virtual void TurretGunShake(float value) override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TurretRocketShake(float value);
};

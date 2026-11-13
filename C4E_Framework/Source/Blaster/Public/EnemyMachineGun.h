// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemyTurret.h"
#include "EnemyMachineGun.generated.h"

UCLASS()
class BLASTER_API AEnemyMachineGun : public ABaseEnemyTurret
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyMachineGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

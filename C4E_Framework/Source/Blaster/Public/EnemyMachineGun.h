// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemyTurret.h"
#include "EnemyMachineGun.generated.h"

class UArrowComponent;

UCLASS(ABSTRACT)
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> _arrow;
	
	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void TurretFire() override;
	
	virtual void TurretGunShake(float value) override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void beamtarget(FVector start, FVector end, bool didHit);
};

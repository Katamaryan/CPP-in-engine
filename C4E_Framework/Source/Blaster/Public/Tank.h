// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Inputable.h"
#include "Components/TimelineComponent.h"
#include "Tank.generated.h"

class UTimelineComponent;
class ATankShot;
class UArrowComponent;

class UStaticMeshComponent;
class UHealthComponent;
class UCameraComponent;
class USpringArmComponent;
class UCascadeParticleSystemComponent;

UCLASS(Abstract)
class BLASTER_API ATank : public ACharacter, public IInputable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UArrowComponent>> _arrow;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UStaticMeshComponent>> _staticMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UCascadeParticleSystemComponent>> _particleSystem;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> _springArm;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> _camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _health;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCapsuleComponent> _playerCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATankShot> TankShot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UParticleSystem> Shotbase;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTimelineComponent> Gun1Recoil;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTimelineComponent> Gun2Recoil;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCurveFloat> RecoilCurve;
	FOnTimelineFloat OnGun1Update;
	FOnTimelineFloat OnGun2Update;
	int FirePoint;
	bool Gun01;
	bool GunSide = true;
	bool GunBarrel = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanFire;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector RespawnPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RespawnTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle RespawnTimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle ResetFireTimerHandle;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void IMove_Implementation(float inputValue) override;
	virtual void ITurn_Implementation(float inputValue) override;
	virtual void IPrimaryAction_Implementation(bool inputClicked) override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void FireProjectile(UArrowComponent* firePoint, bool gun01);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Respawn();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ResetFire();
	UFUNCTION()
	void Gun1Tick(float value);
	UFUNCTION()
	void Gun2Tick(float value);
};

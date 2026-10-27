// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Inputable.h"
#include "Tank.generated.h"

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
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void IMove_Implementation(float inputValue) override;
	virtual void ITurn_Implementation(float inputValue) override;
	virtual void IPrimaryAction_Implementation(bool inputClicked) override;
};

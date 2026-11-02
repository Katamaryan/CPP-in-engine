// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TankShot.generated.h"

class USphereComponent;

UCLASS(ABSTRACT)
class BLASTER_API ATankShot : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATankShot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> Sphere;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UParticleSystem> TankShotFail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UParticleSystem> TankShotHit;
	
	bool HasCollided;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CollisionHandler(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);
	UFUNCTION(BlueprintNativeEvent)
	void KillShot();
	
private:
	FTimerHandle TimerHandle;
};

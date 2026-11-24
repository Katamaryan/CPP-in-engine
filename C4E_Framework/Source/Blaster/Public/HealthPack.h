// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "HealthPack.generated.h"

class UTimelineComponent;
class USphereComponent;

UCLASS()
class BLASTER_API AHealthPack : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHealthPack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> _sphere;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _healthPack;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTimelineComponent> _bobTimeline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCurveFloat> _bobCurve;
	FOnTimelineFloat _onBobUpdate;
	
	UFUNCTION(BlueprintCallable, blueprintNativeEvent)
	void HandleCollisionStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable, blueprintNativeEvent)
	void HealthPackBob(float value);
};

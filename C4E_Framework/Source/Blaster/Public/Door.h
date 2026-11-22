// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UTimelineComponent;

UCLASS(ABSTRACT)
class BLASTER_API ADoor : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _doorMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETimelineDirection::Type> _doorDirection;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTimelineComponent> _doorTimeline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCurveFloat> _doorCurve;
	FOnTimelineFloat _onDoorUpdate;
	FOnTimelineEvent _onDoorFinish;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector DoorOpenOffset;
	FVector DoorClosed;
	bool bIsOpen;
	
	virtual void Interact_Implementation(APawn* InteractorPawn) override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void MoveDoor(float value);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopDoor();
};

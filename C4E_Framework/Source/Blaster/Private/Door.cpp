// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "Kismet/KismetMathLibrary.h"


// Sets default values
ADoor::ADoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	_doorMesh = CreateDefaultSubobject<UStaticMeshComponent>("DoorMesh");
	_doorMesh->SetupAttachment(RootComponent);
	
	_doorTimeline = CreateDefaultSubobject<UTimelineComponent>("DoorTimeline");
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	DoorClosed = _doorMesh->GetComponentLocation();
	
	if (_doorCurve)
	{
		_onDoorUpdate.BindDynamic(this, &ADoor::MoveDoor);
		_doorTimeline->AddInterpFloat(_doorCurve, _onDoorUpdate);
		_onDoorFinish.BindDynamic(this, &ADoor::StopDoor);
		_doorTimeline->AddEvent(0.5, _onDoorFinish);
		_doorTimeline->SetDirectionPropertyName(FName(TEXT("_doorDirection")));
	}
}

void ADoor::Interact_Implementation(APawn* InteractorPawn)
{
	IInteractable::Interact_Implementation(InteractorPawn);
	
	if (InteractorPawn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, 
			FString::Printf(TEXT("%p Opened Door"), InteractorPawn));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
			FString::Printf(TEXT("Door Open")));
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
			FString::Printf(TEXT("%hs"), bIsOpen? "true" : "false" ));
	if (bIsOpen)
		_doorTimeline->Stop();
	else
		_doorTimeline->Play();
	
}

void ADoor::MoveDoor_Implementation(float value)
{
	_doorMesh->SetWorldLocation(UKismetMathLibrary::VLerp(DoorClosed, DoorClosed + DoorOpenOffset, value));
}

void ADoor::StopDoor_Implementation()
{
	if (_doorDirection == ETimelineDirection::Forward)
	{
		bIsOpen = true;
	}
	else
	{
		bIsOpen = false;
	}
}



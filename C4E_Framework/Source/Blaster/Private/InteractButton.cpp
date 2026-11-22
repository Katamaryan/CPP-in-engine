// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractButton.h"

#include "Interactable.h"
#include "Components/SphereComponent.h"


// Sets default values
AInteractButton::AInteractButton()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	_buttonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	_buttonMesh->SetupAttachment(RootComponent);
	_buttonMesh->SetWorldScale3D(FVector(0.5, 0.5, 0.05));
	_sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	_sphere->SetupAttachment(_buttonMesh);
	_sphere->SetWorldScale3D(FVector(2.0f, 2.0f, 20.0f));
	_sphere->SetSphereRadius(32.0f);
}

// Called when the game starts or when spawned
void AInteractButton::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AInteractButton::HandleCollisionStart);
	OnActorEndOverlap.AddDynamic(this, &AInteractButton::HandleCollisionEnd);
}

void AInteractButton::ButtonTriggered_Implementation()
{
	_buttonMesh->SetMaterial(0, _gridGood);
	bIsPressed = true;
}

void AInteractButton::ResetButton_Implementation()
{
	_buttonMesh->SetMaterial(0, _gridDanger);
	bIsPressed = false;
}

void AInteractButton::HandleCollisionEnd_Implementation(AActor* OverlappedActor, AActor* OtherActor)
{
	TArray<AActor*> OverlappingActors;
	_sphere->GetOverlappingActors(OverlappingActors, APawn::StaticClass());
	if (OverlappingActors.Num() == 0)
		ResetButton();
}

void AInteractButton::HandleCollisionStart_Implementation(AActor* OverlappedActor, AActor* OtherActor)
{
	APawn* pawn = Cast<APawn>(OtherActor);
	
	if (bIsPressed) {return;}
	
	for (int i = 0; i< LinkedActors.Num(); i++)
	{
		if (LinkedActors[i]->Implements<UInteractable>())
		{
			IInteractable::Execute_Interact(LinkedActors[i], pawn);
		}
	}
	ButtonTriggered();
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "EndPoint.h"

#include "Tank.h"
#include "Components/SphereComponent.h"


// Sets default values
AEndPoint::AEndPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	_sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	RootComponent = _sphere;
	_sphere->SetSphereRadius(100.0f);
	_endMesh = CreateDefaultSubobject<UStaticMeshComponent>("EndMesh");
	_endMesh->SetupAttachment(_sphere);
	_endMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 5.0f));
	_endMesh->SetWorldScale3D(FVector(100.0f, 100.0f, 10.0f));
}

// Called when the game starts or when spawned
void AEndPoint::BeginPlay()
{
	Super::BeginPlay();
	
	_endMesh->SetVisibility(bAutoActivate);
	bAutoActivate?
	_sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly):
	_sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (bAutoActivate)
		OnEndActivated.Broadcast();
}

void AEndPoint::Interact_Implementation(APawn* InteractorPawn)
{
	IInteractable::Interact_Implementation(InteractorPawn);

	if (bAutoActivate) {return;}
	
	_endMesh->SetVisibility(true);
	_sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	
	OnEndActivated.Broadcast();
}

void AEndPoint::HandleCollisionStart_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                    UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, FHitResult SweepResult)
{
	if (OtherActor->IsA(ATank::StaticClass()))
		OnEndReached.Broadcast();
}


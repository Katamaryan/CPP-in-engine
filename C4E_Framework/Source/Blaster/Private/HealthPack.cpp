// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPack.h"

#include "Tank.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AHealthPack::AHealthPack()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_sphere = CreateDefaultSubobject<USphereComponent>(FName("Sphere"));
	RootComponent = _sphere;
	_sphere->SetSphereRadius(75.0f);
	_healthPack = CreateDefaultSubobject<UStaticMeshComponent>(FName("HealthPack"));
	_healthPack->SetupAttachment(RootComponent);
	
	_bobTimeline = CreateDefaultSubobject<UTimelineComponent>(FName("Bob"));
}

// Called when the game starts or when spawned
void AHealthPack::BeginPlay()
{
	Super::BeginPlay();
	
	_sphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &AHealthPack::HandleCollisionStart);

	_onBobUpdate.BindDynamic(this, &AHealthPack::HealthPackBob);
	_bobTimeline->AddInterpFloat(_bobCurve, _onBobUpdate);
	_bobTimeline->SetLooping(true);
	
	_bobTimeline->PlayFromStart();
}

void AHealthPack::HealthPackBob_Implementation(float value)
{
	_healthPack->SetWorldLocation(UKismetMathLibrary::VLerp(_healthPack->GetComponentLocation(), _healthPack->GetComponentLocation() + FVector(0.0f, 0.0f, 1.0f), value));
	
}

void AHealthPack::HandleCollisionStart_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
                                                      UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ATank::StaticClass()))
	{
		UGameplayStatics::ApplyDamage(OtherActor, -20, nullptr, nullptr, nullptr);
		_sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		_healthPack->SetVisibility(false);
	}
}



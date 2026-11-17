// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyLighting.h"

#include "Particles/ParticleSystemComponent.h"


// Sets default values
AEnemyLighting::AEnemyLighting()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	_rig.Add(CreateDefaultSubobject<UStaticMeshComponent>(FName("Rig01")));
	_rig[0]->SetupAttachment(_staticMesh[1]);
	_rig[0]->SetRelativeLocation(FVector(0.0f, 26.0f, 28.0f));
	_lightningCharge.Add(CreateDefaultSubobject<UParticleSystemComponent>(FName("LightingCharge01")));
	_lightningCharge[0]->SetupAttachment(_rig[0]);
	_lightningCharge[0]->SetRelativeLocation(FVector(0.0f, -5.0f, 0.0f));
	
	_rig.Add(CreateDefaultSubobject<UStaticMeshComponent>(FName("Rig02")));
	_rig[1]->SetupAttachment(_staticMesh[1]);
	_rig[1]->SetRelativeLocation(FVector(0.0f, -26.0f, 28.0f));
	_lightningCharge.Add(CreateDefaultSubobject<UParticleSystemComponent>(FName("LightingCharge02")));
	_lightningCharge[1]->SetupAttachment(_rig[1]);
	_lightningCharge[1]->SetRelativeLocation(FVector(0.0f, -2.5f, 0.0f));
	_lightningCharge[1]->SetRelativeRotation(FRotator(0.0f, 0.0f, -180.0f));
	
}

// Called when the game starts or when spawned
void AEnemyLighting::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyLighting::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyTurret.h"

#include "HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CascadeParticleSystemComponent.h"


// Sets default values
ABaseEnemyTurret::ABaseEnemyTurret()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	_box = CreateDefaultSubobject<UBoxComponent>(FName("Box"));
	RootComponent = _box;
	
	_staticMesh.Add(CreateDefaultSubobject<UStaticMeshComponent>(FName("Baseplate")));
	_staticMesh[0]->SetupAttachment(RootComponent);
	_staticMesh.Add(CreateDefaultSubobject<UStaticMeshComponent>(FName("TurrestSpin")));
	_staticMesh[1]->SetupAttachment(_staticMesh[0]);
	_staticMesh.Add(CreateDefaultSubobject<UStaticMeshComponent>(FName("DangerZone")));
	_staticMesh[2]->SetupAttachment(RootComponent);
	_health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	
	_staticMesh[2]->SetWorldScale3D(FVector(Range, Range, 50.0f));
}

// Called when the game starts or when spawned
void ABaseEnemyTurret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEnemyTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseEnemyTurret::Fire_Implementation()
{
}

void ABaseEnemyTurret::TurretDestroyed_Implementation(AController* InstigatedBy, AActor* Causer)
{
	UGameplayStatics::SpawnEmitterAtLocation(this, EnemyDeath, GetActorLocation(), GetActorRotation());
}


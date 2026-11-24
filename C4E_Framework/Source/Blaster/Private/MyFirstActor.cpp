// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFirstActor.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AMyFirstActor::AMyFirstActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	_collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = _collider;
	
	_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	_staticMesh->SetupAttachment(_collider);
}

void AMyFirstActor::HandleDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	GetWorldTimerManager().SetTimer(_timer, this, &AMyFirstActor::BlowUp, 0.25f, false);
}

void AMyFirstActor::BlowUp()
{
	ETraceTypeQuery TraceChannel = UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1);
	FHitResult Hit;
	UKismetSystemLibrary::SphereTraceSingle(this, GetActorLocation(),GetActorLocation() + FVector(0.0f, 0.0f, 1.0f)
		, 150.0f, TraceChannel, false, {}, EDrawDebugTrace::None, Hit, true );

	UGameplayStatics::ApplyDamage(Hit.GetActor(), 5.0f, nullptr, nullptr, nullptr);
	
	UGameplayStatics::SpawnEmitterAtLocation(this, _explosion, GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), FVector(5.0f, 10.0f, 10.0f));
	Destroy();
}

void AMyFirstActor::BeginPlay()
{
	Super::BeginPlay();
	
	OnTakeAnyDamage.AddDynamic(this, &AMyFirstActor::HandleDamage);
}




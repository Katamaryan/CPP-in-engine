// Fill out your copyright notice in the Description page of Project Settings.


#include "Rocket.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ARocket::ARocket()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	_sphere = CreateDefaultSubobject<USphereComponent>(FName("Sphere"));
	RootComponent = _sphere;
	_rocketBase = CreateDefaultSubobject<UParticleSystemComponent>(FName("RocketBase"));
	_rocketBase->SetupAttachment(RootComponent);
	_projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
}

// Called when the game starts or when spawned
void ARocket::BeginPlay()
{
	Super::BeginPlay();
	
	_sphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &ARocket::Handle_Collision);
}

void ARocket::Handle_Collision_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bHasCollided) {return;}
	
	bHasCollided = true;
	ETraceTypeQuery TraceChannel = UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1);
	FHitResult Hit;
	
	UKismetSystemLibrary::SphereTraceSingle(this, GetActorLocation(),GetActorLocation() + FVector(0.0f, 0.0f, 1.0f)
		, 50.0f, TraceChannel, false, {}, EDrawDebugTrace::None, Hit, true );

	UGameplayStatics::ApplyDamage(Hit.GetActor(), 5.0f, nullptr, nullptr, nullptr);
	
	UGameplayStatics::SpawnEmitterAtLocation(this, _rocketExplosion, GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f));
	Destroy();
}




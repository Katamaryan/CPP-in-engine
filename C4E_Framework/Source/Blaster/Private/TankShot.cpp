// Fill out your copyright notice in the Description page of Project Settings.


#include "TankShot.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
ATankShot::ATankShot()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Sphere);
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

// Called when the game starts or when spawned
void ATankShot::BeginPlay()
{
	Super::BeginPlay();
	
	//bruh, i didnt know i had to bind the collision event to the function
	Sphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &ATankShot::CollisionHandler);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATankShot::KillShot, 0.75f, false);
}

void ATankShot::KillShot_Implementation()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, TankShotFail, GetActorLocation(),GetActorRotation(), FVector(1.0f, 1.0f, 1.0f));
	Destroy();
}


void ATankShot::CollisionHandler_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                                bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasCollided)
		return;
	
	HasCollided = true;
	
	UGameplayStatics::ApplyDamage(OtherActor, 1.0, GetInstigatorController(), this, NULL);
	if (TankShotHit)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, TankShotHit, GetActorLocation(), 
			FRotator(0.0f, 0.0f, 0.0f), FVector(0.5f, 0.5f, 0.5f));
	}
	Destroy();
}




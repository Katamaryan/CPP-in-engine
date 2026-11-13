// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyTurret.h"

#include "HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "TargetComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ABaseEnemyTurret::ABaseEnemyTurret()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	_box = CreateDefaultSubobject<UBoxComponent>(FName("Box"));
	RootComponent = _box;
	
	_staticMesh.Add(CreateDefaultSubobject<UStaticMeshComponent>(FName("Baseplate")));
	_staticMesh[0]->SetupAttachment(RootComponent);
	_staticMesh.Add(CreateDefaultSubobject<UStaticMeshComponent>(FName("TurretSpin")));
	_staticMesh[1]->SetupAttachment(_staticMesh[0]);
	_staticMesh.Add(CreateDefaultSubobject<UStaticMeshComponent>(FName("DangerZone")));
	_staticMesh[2]->SetupAttachment(RootComponent);
	_health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	_target = CreateDefaultSubobject<UTargetComponent>(TEXT("Target"));
	
	_staticMesh[2]->SetWorldScale3D(FVector(Range, Range, 50.0f));
}

// Called when the game starts or when spawned
void ABaseEnemyTurret::BeginPlay()
{
	Super::BeginPlay();
	
	_health->ResetHealth();
	_health->OnDeath.AddUniqueDynamic(this, &ABaseEnemyTurret::TurretDestroyed);
	TankREF = UGameplayStatics::GetActorOfClass(this, ATank::StaticClass());
	
	GetWorldTimerManager().SetTimer(FireRateHandle, this, &ABaseEnemyTurret::Fire, FireRate, true);

	if (RecoilCurve)
	{
		OnTurretUpdate.BindDynamic(this, &ABaseEnemyTurret::TurretGunShake);
		TurretRecoil->AddInterpFloat(RecoilCurve, OnTurretUpdate);
	}
}

// Called every frame
void ABaseEnemyTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!IsValid(TankREF)) { return; }
	
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(_staticMesh[1]->GetComponentLocation(), TankREF->GetActorLocation());
	FRotator newRotation = UKismetMathLibrary::RInterpTo(_staticMesh[1]->GetComponentRotation(), TargetRotation, DeltaTime, 2.0f);
	_staticMesh[1]->SetWorldRotation(FRotator(0.0f, newRotation.Yaw, 0.0f));
}

void ABaseEnemyTurret::TurretGunShake_Implementation(float value)
{
	_staticMesh[1]->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, value + 7), FRotator(0.0f - value, _staticMesh[1]->GetRelativeRotation().Yaw, 0.0f));
}

void ABaseEnemyTurret::TurretFire()
{
}

void ABaseEnemyTurret::Fire_Implementation()
{
	ETraceTypeQuery PlayerTraceType= UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel1);
	FHitResult HitResult;
	if (UKismetSystemLibrary::SphereTraceSingle(this,GetActorLocation(),  FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 1.0f), Range, PlayerTraceType, false, {}, EDrawDebugTrace::ForDuration, HitResult, true))
	{
		TurretFire();
	}
		
}

void ABaseEnemyTurret::TurretDestroyed_Implementation(AController* InstigatedBy, AActor* Causer)
{
	UGameplayStatics::SpawnEmitterAtLocation(this, EnemyDeath, GetActorLocation(), FRotator(0, 0, 0));
	Destroy();
}


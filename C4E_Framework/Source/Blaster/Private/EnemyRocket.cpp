// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyRocket.h"

#include "Components/ArrowComponent.h"
#include "Rocket.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AEnemyRocket::AEnemyRocket()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	_rig.Add(CreateDefaultSubobject<UStaticMeshComponent>(FName("Rig01")));
	_rig[0]->SetupAttachment(_staticMesh[1]);
	_rig[0]->SetRelativeLocation(FVector(0.0f, 20.0f, 30.0f));
	_rig[0]->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	_turretPod.Add(CreateDefaultSubobject<UStaticMeshComponent>(FName("TurretPod01")));
	_turretPod[0]->SetupAttachment(_rig[0]);
	_turretPod[0]->SetRelativeLocation(FVector(0.0f, -2.0f, 0.0f));
	_turretPod[0]->SetRelativeRotation(FRotator(0.0f, -180.0f, 0.0f));
	_arrow.Add(CreateDefaultSubobject<UArrowComponent>(FName("Arrow01")));
	_arrow[0]->SetupAttachment(_turretPod[0]);
	_arrow[0]->SetRelativeLocation(FVector(10.0f, -1.0f, 0.0f));
	_arrow[0]->SetArrowSize(0.2f);
	
	_rig.Add(CreateDefaultSubobject<UStaticMeshComponent>(FName("Rig02")));
	_rig[1]->SetupAttachment(_staticMesh[1]);
	_rig[1]->SetRelativeLocation(FVector(0.0f, -20.0f, 30.0f));
	_turretPod.Add(CreateDefaultSubobject<UStaticMeshComponent>(FName("TurretPod02")));
	_turretPod[1]->SetupAttachment(_rig[1]);
	_turretPod[1]->SetRelativeLocation(FVector(0.0f, -2.0f, 0.0f));
	_arrow.Add(CreateDefaultSubobject<UArrowComponent>(FName("Arrow02")));
	_arrow[1]->SetupAttachment(_turretPod[1]);
	_arrow[1]->SetRelativeLocation(FVector(10.0f, 1.0f, 0.0f));
	_arrow[1]->SetArrowSize(0.2f);
	
	RocketShake = CreateDefaultSubobject<UTimelineComponent>(FName("RocketShake"));
}

// Called when the game starts or when spawned
void AEnemyRocket::BeginPlay()
{
	Super::BeginPlay();
	
	if (RocketCurve)
	{
		OnRocketUpdate.BindDynamic(this, &AEnemyRocket::TurretRocketShake);
		RocketShake->AddInterpFloat(RocketCurve, OnRocketUpdate);
	}
}

// Called every frame
void AEnemyRocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyRocket::TurretFire()
{
	Super::TurretFire();
	
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	spawnParams.Owner = this;
	
	FVector TankLocation = FVector(TankREF->GetActorLocation().X, TankREF->GetActorLocation().Y, TankREF->GetActorLocation().Z - 20.0f);
	
	FVector arrow01Location = _arrow[0]->GetComponentLocation();
	FRotator arrow01Rotation = FRotator(UKismetMathLibrary::FindLookAtRotation(arrow01Location, TankLocation).Pitch, _arrow[0]->GetComponentRotation().Yaw, _arrow[0]->GetComponentRotation().Yaw);
	
	FVector arrow02Location = _arrow[1]->GetComponentLocation();
	FRotator arrow02Rotation = FRotator(UKismetMathLibrary::FindLookAtRotation(arrow02Location, TankLocation).Pitch, _arrow[1]->GetComponentRotation().Yaw, _arrow[1]->GetComponentRotation().Yaw);
	
	if (bPoint)
	{
		GetWorld()->SpawnActor(_rocket, &arrow01Location, &arrow01Rotation, spawnParams);
	}
	else
	{
		GetWorld()->SpawnActor(_rocket, &arrow02Location, &arrow02Rotation, spawnParams);
		
	}
	TurretRecoil->PlayFromStart();
	RocketShake->PlayFromStart();
	bPoint = !bPoint;
}

void AEnemyRocket::TurretGunShake(float value)
{
	Super::TurretGunShake(value);
	_staticMesh[1]->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, value + 7), FRotator(0.0f - value, _staticMesh[1]->GetRelativeRotation().Yaw, 0.0f));
}

void AEnemyRocket::TurretRocketShake_Implementation(float value)
{
	if (!bPoint)
		_turretPod[0]->SetRelativeLocation(FVector(0.0f, value, 0.0f));
	else
		_turretPod[1]->SetRelativeLocation(FVector(0.0f, value, 0.0f));
}


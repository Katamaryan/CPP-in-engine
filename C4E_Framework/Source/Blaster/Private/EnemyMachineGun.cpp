// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMachineGun.h"

#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AEnemyMachineGun::AEnemyMachineGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	_arrow = CreateDefaultSubobject<UArrowComponent>(TEXT ("ArrowComponent"));
	_arrow->SetupAttachment(_staticMesh[1]);
	_arrow->SetArrowSize(0.2f);
	_arrow->SetRelativeLocation(FVector(32.0f, 0.0f, 18.0f));


}

// Called when the game starts or when spawned
void AEnemyMachineGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyMachineGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyMachineGun::TurretFire()
{
	Super::TurretFire();
	
	FHitResult HitResult;
	ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(ECC_Visibility);
	if (UKismetSystemLibrary::LineTraceSingle(this, _arrow->GetComponentLocation(), 
		UKismetMathLibrary::GetForwardVector(_arrow->GetComponentRotation()) * 500 + _arrow->GetComponentLocation(),
		TraceType, false, {}, EDrawDebugTrace::ForDuration, HitResult, false))
	{
		UGameplayStatics::ApplyDamage(HitResult.GetActor(), 1, nullptr, nullptr, nullptr);
		beamtarget(_arrow->GetComponentLocation(), HitResult.ImpactPoint, true);
	}
	else
	{
		beamtarget(_arrow->GetComponentLocation(), UKismetMathLibrary::GetForwardVector(_arrow->GetComponentRotation()) * 500 + _arrow->GetComponentLocation(), false);
	}
	
	TurretRecoil->PlayFromStart();
}

void AEnemyMachineGun::TurretGunShake(float value)
{
	Super::TurretGunShake(value);
	
	_staticMesh[1]->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, value + 7), FRotator(0.0f - value, _staticMesh[1]->GetRelativeRotation().Yaw, 0.0f));
}


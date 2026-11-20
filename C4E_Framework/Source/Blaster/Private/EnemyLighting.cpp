// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyLighting.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AEnemyLighting::AEnemyLighting()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	_rig.Add(CreateDefaultSubobject<UStaticMeshComponent>(FName("Rig01")));
	_rig[0]->SetupAttachment(_staticMesh[1]);
	_rig[0]->SetRelativeLocation(FVector(0.0f, 26.0f, 28.0f));
	_rig[0]->SetRelativeRotation(FRotator(0.0f, 0.0f, 180.0f));
	_rig[0]->SetWorldScale3D(FVector(1.0f, 2.0f, 1.0f));
	_lightningCharge.Add(CreateDefaultSubobject<UParticleSystemComponent>(FName("LightingCharge01")));
	_lightningCharge[0]->SetupAttachment(_rig[0]);
	_lightningCharge[0]->SetRelativeLocation(FVector(0.0f, -5.0f, 0.0f));
	_lightningCharge[0]->SetRelativeRotation(FRotator(0.0f, 0.0f, -180.0f));
	_lightningCharge[0]->SetWorldScale3D(FVector(1.0f, 0.5f, 1.0f));
	
	_rig.Add(CreateDefaultSubobject<UStaticMeshComponent>(FName("Rig02")));
	_rig[1]->SetupAttachment(_staticMesh[1]);
	_rig[1]->SetRelativeLocation(FVector(0.0f, -26.0f, 28.0f));
	_rig[1]->SetWorldScale3D(FVector(1.0f, 2.0f, 1.0f));
	_lightningCharge.Add(CreateDefaultSubobject<UParticleSystemComponent>(FName("LightingCharge02")));
	_lightningCharge[1]->SetupAttachment(_rig[1]);
	_lightningCharge[1]->SetRelativeLocation(FVector(0.0f, -2.5f, 0.0f));
	_lightningCharge[1]->SetWorldScale3D(FVector(1.0f, 0.5f, 1.0f));
	
}

// Called when the game starts or when spawned
void AEnemyLighting::BeginPlay()
{
	Super::BeginPlay();
	
	if (FireCurve)
	{
		OnFire.BindDynamic(this, &AEnemyLighting::LightningFire);
		TurretRecoil->AddEvent(0.8f, OnFire);
	}
	
	if (FXBuildupCurve)
	{
		OnTurretUpdate.BindDynamic(this, &ABaseEnemyTurret::TurretGunShake);
		TurretRecoil->AddInterpFloat(FXBuildupCurve, OnTurretUpdate);
	}
}

// Called every frame
void AEnemyLighting::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyLighting::TurretFire()
{
	Super::TurretFire();
	
	TurretRecoil->PlayFromStart();
}

void AEnemyLighting::TurretGunShake(float value)
{
	Super::TurretGunShake(value);

	float value1 = RecoilCurve->GetFloatValue(TurretRecoil->GetPlaybackPosition());
	float value2 = FXBuildupCurve->GetFloatValue(TurretRecoil->GetPlaybackPosition());
	
	_staticMesh[1]->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, (value1 * 5) + 7), FRotator(0.0f - value, _staticMesh[1]->GetRelativeRotation().Yaw, 0.0f));
	
	
		_lightningCharge[0]->SetFloatParameter(FName("LT1"), value2 * 40);
		_lightningCharge[0]->SetFloatParameter(FName("LT2"), value2 * 300);
	
		_lightningCharge[1]->SetFloatParameter(FName("LT1"), value2 * 40);
		_lightningCharge[1]->SetFloatParameter(FName("LT2"), value2 * 300);
		
}

void AEnemyLighting::LightningFire_Implementation()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, LightningBlast, GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f));
	
	//idk why unreal makes you put random extra crap for no reason like this
	TArray<FHitResult> outHits;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	FVector start = GetActorLocation();
	FVector end = GetActorLocation() + FVector(0.0f, 0.0f, 1.0f);
	UKismetSystemLibrary::SphereTraceMultiForObjects(this, start, end , Range, ObjectTypes, 
		false, {}, EDrawDebugTrace::None, outHits, true);
	for (int i = 0; i < outHits.Num(); i++)
	{
		AActor* hitActor = outHits[i].GetActor();
		UPrimitiveComponent* hitComponent = outHits[i].GetComponent();
		UGameplayStatics::ApplyDamage(hitActor, 5.0f, nullptr, nullptr, nullptr);
		UGameplayStatics::SpawnEmitterAttached(LightningHit, hitComponent, FName("None"), FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	}
	
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "CascadeParticleSystemComponent.h"
#include "HealthComponent.h"
#include "TankShot.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ATank::ATank()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//CapsuleComponent->SetCapsuleHalfHeight(25.22f);
	int a = 0;
	_arrow.Add(CreateDefaultSubobject<UArrowComponent>(TEXT("RotTracks")));
	_arrow[a]->SetupAttachment(RootComponent);
	
	int s = 0;
	_staticMesh.Add(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane")));
	_staticMesh[s]->SetupAttachment(_arrow[0]);
	_staticMesh[s]->SetRelativeLocation(FVector(40.0f,0.0f,0.0f));
	_staticMesh[s]->SetRelativeRotation(FRotator(0.0f,90.0f,0.0f));
	_staticMesh[s]->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
	
	s = s+1;
	_staticMesh.Add(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Track01")));
	_staticMesh[s]->SetupAttachment(_arrow[0]);
	_staticMesh[s]->SetRelativeLocation(FVector(0.0f,10.0f,-20.0f));
	
	int p = 0;
	_particleSystem.Add(CreateDefaultSubobject<UCascadeParticleSystemComponent>(TEXT("Treads01")));
	_particleSystem[p]->SetupAttachment(_staticMesh[1]);
	
	s = s+1;
	_staticMesh.Add(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Track02")));
	_staticMesh[s]->SetupAttachment(_arrow[0]);
	_staticMesh[s]->SetRelativeLocation(FVector(0.0f,-10.0f,-20.0f));
	
	p = p+1;
	_particleSystem.Add(CreateDefaultSubobject<UCascadeParticleSystemComponent>(TEXT("Treads02")));
	_particleSystem[p]->SetupAttachment(_staticMesh[2]);
	
	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_springArm->SetupAttachment(RootComponent);
	_springArm->SetRelativeRotation(FRotator(-70.0f, 0.0f, 0.0f));
	_springArm->TargetArmLength = 500.0f ;
	_springArm->bDoCollisionTest = false;
	_springArm->bEnableCameraLag = true;
	
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_camera->SetupAttachment(_springArm);
	
	s = s+1;
	_staticMesh.Add(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TCore01")));
	_staticMesh[s]->SetupAttachment(RootComponent);
	
	s = s+1;
	_staticMesh.Add(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TGun01")));
	_staticMesh[s]->SetupAttachment(_staticMesh[3]);
	_staticMesh[s]->SetRelativeLocation(FVector(0.0f,15.0f,0.0f));
	
	a = a+1;
	_arrow.Add(CreateDefaultSubobject<UArrowComponent>(TEXT("W1")));
	_arrow[a]->SetupAttachment(_staticMesh[4]);
	_arrow[a]->SetRelativeLocation(FVector(34.0f,0.0f,5.5f));
	
	a = a+1;
	_arrow.Add(CreateDefaultSubobject<UArrowComponent>(TEXT("W2")));
	_arrow[a]->SetupAttachment(_staticMesh[4]);
	_arrow[a]->SetRelativeLocation(FVector(34.0f,0.0f,-5.5f));
	
	s = s+1;
	_staticMesh.Add(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TGun02")));
	_staticMesh[s]->SetupAttachment(_staticMesh[3]);
	_staticMesh[s]->SetRelativeLocation(FVector(0.0f, -15.0f, 0.0f));
	
	a = a+1;
	_arrow.Add(CreateDefaultSubobject<UArrowComponent>(TEXT("W3")));
	_arrow[a]->SetupAttachment(_staticMesh[5]);
	_arrow[a]->SetRelativeLocation(FVector(34.0f, .0f, 5.5f));
	
	a = a+1;
	_arrow.Add(CreateDefaultSubobject<UArrowComponent>(TEXT("W4")));
	_arrow[a]->SetupAttachment(_staticMesh[5]);
	_arrow[a]->SetRelativeLocation(FVector(34.0f, .0f, -5.5f));
	
	_health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	
	Gun1Recoil = CreateDefaultSubobject<UTimelineComponent>(TEXT("Gun1 Timeline"));
	Gun2Recoil = CreateDefaultSubobject<UTimelineComponent>(TEXT("Gun2 Timeline"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	if (RecoilCurve)
	{
		OnGun1Update.BindDynamic(this, &ATank::Gun1Tick);
		Gun1Recoil->AddInterpFloat(RecoilCurve, OnGun1Update);
		OnGun2Update.BindDynamic(this, &ATank::Gun2Tick);
		Gun2Recoil->AddInterpFloat(RecoilCurve, OnGun2Update);
	}
	if (_health)
	{
		_health->OnHealthModified.AddUniqueDynamic(this, &ATank::HealthChangedHandler);
		_health->OnDeath.AddUniqueDynamic(this, &ATank::TankDestroyed);
	}	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	ETraceTypeQuery TraceType= UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility);
	FHitResult HitResult;
	GetLocalViewingPlayerController()->GetHitResultUnderCursorByChannel(TraceType, true, HitResult);
	FVector newVector = FVector(HitResult.Location.X, HitResult.Location.Y, _staticMesh[3]->GetComponentLocation().Z);
	
	FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(_staticMesh[3]->GetComponentLocation(), newVector);
	
	_staticMesh[3]->SetWorldRotation(newRotation);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::IMove_Implementation(float inputValue)
{
	AddMovementInput(_arrow[0]->GetComponentRotation().Vector() * inputValue, 0.5f, false);
}

void ATank::ITurn_Implementation(float inputValue)
{
	_arrow[0]->AddRelativeRotation(FRotator(0.0f, inputValue, 0.0f));
}

void ATank::IPrimaryAction_Implementation(bool inputClicked)
{
	//this one is crap  and i think it stinks cus i cant properly see it while im debugging easily
	//UE_LOG(LogTemp, Warning, TEXT("IPRIMARYACTION_IMPLEMENTATION called with value %hhd"), inputClicked);
	
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
	//	FString::Printf(TEXT("Projectile fire from %hhd"), Gun01));
	
	if (!inputClicked) {return;}
	
	if (_health->bIsDead) {return;}
	
	if (bCanFire)
	{
		
		bCanFire = false;
		
		if (GunSide)
		{
			if (GunBarrel)
				FirePoint = 1;
			else
				FirePoint = 2;
			Gun01 = true;
		}
		else
		{
			if (GunBarrel)
				FirePoint = 3;
			else
				FirePoint = 4;
			GunBarrel = !GunBarrel;
			Gun01 = false;
		}
		GunSide = !GunSide;
		
		FireProjectile_Implementation(_arrow[FirePoint], Gun01);
	}
}

void ATank::Gun1Tick(float value)
{
	_staticMesh[4]->SetRelativeLocation(FVector(value, 15.0f, 0.0f));
}

void ATank::Gun2Tick(float value)
{
	_staticMesh[5]->SetRelativeLocation(FVector(value, -15.0f, 0.0f));
	
}

void ATank::TankDestroyed_Implementation(AController* InstigatedBy, AActor* Causer)
{
	if (RespawnTimerHandle.IsValid()) {return;}
	
	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetVisibility(false, true);
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathExplosion, GetActorLocation(), GetActorRotation());
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ATank::Respawn_Implementation, RespawnTime);
}

void ATank::HealthChangedHandler_Implementation(bool bPositive, float newHealth, float healthDelta, float healthRatio)
{
	OnHealthUpdated.Broadcast(healthRatio);
}

void ATank::ResetFire_Implementation()
{
	bCanFire = true;
}

void ATank::Respawn_Implementation()
{
	SetActorLocation(RespawnPoint);
	_health->ResetHealth();
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	GetRootComponent()->SetVisibility(true, true);
	GetWorldTimerManager().ClearTimer(RespawnTimerHandle);
}

void ATank::FireProjectile_Implementation(UArrowComponent* firePoint, bool gun01)
{
	if (!TankShot)
		return;
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Instigator = this;
	FVector SpawnLocation = firePoint->GetComponentLocation();
	FRotator SpawnRotation = firePoint->GetComponentRotation();
	GetWorld()->SpawnActor(TankShot, &SpawnLocation, &SpawnRotation, SpawnParameters);
	
	UGameplayStatics::SpawnEmitterAtLocation(this, Shotbase, SpawnLocation, 
			SpawnRotation, FVector(1.0f, 1.0f, 1.0f));
	
	if (gun01)
		Gun1Recoil->PlayFromStart();
	else
	{
		Gun2Recoil->PlayFromStart();
	}
	
	GetWorldTimerManager().SetTimer(ResetFireTimerHandle, this, &ATank::ResetFire, 0.2f);
}


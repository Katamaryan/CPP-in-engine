// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "CascadeParticleSystemComponent.h"
#include "HealthComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ATank::ATank()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// _arrow.Init(nullptr, 5);
	// _staticMesh.Init(nullptr, 6);
	// _particleSystem.Init(nullptr, 2);
	
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
	
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
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
	
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
		FString::Printf(TEXT("IPRIMARYACTION_IMPLEMENTATION called with value %hhd"), inputClicked));
	
	if (!inputClicked) {return;}
	
	if (_health->bIsDead) {return;}
	
	if (bCanFire)
	{
		//TODO
	}
}

void ATank::Respawn_Implementation()
{
	SetActorLocation(RespawnPoint);
	_health->ResetHealth();
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	GetRootComponent()->SetVisibility(true, true);
	GetWorldTimerManager().ClearTimer(RespawnTimerHandle);
}

void ATank::FireProjectile_Implementation()
{
	//TODO
}


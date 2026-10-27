// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "CascadeParticleSystemComponent.h"
#include "HealthComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ATank::ATank()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	_arrow.Init(nullptr, 5);
	_staticMesh.Init(nullptr, 6);
	_particleSystem.Init(nullptr, 2);
	
	_arrow[0] = CreateDefaultSubobject<UArrowComponent>(TEXT("RotTracks"));
	_arrow[0]->SetupAttachment(RootComponent);
	
	_staticMesh[0] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	_staticMesh[0]->SetupAttachment(_arrow[0]);
	_staticMesh[0]->SetRelativeLocation(FVector(40.0f,0.0f,0.0f));
	_staticMesh[0]->SetRelativeRotation(FRotator(0.0f,90.0f,0.0f));
	_staticMesh[0]->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
	
	_staticMesh[1] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Track01"));
	_staticMesh[1]->SetupAttachment(_arrow[0]);
	_staticMesh[1]->SetRelativeLocation(FVector(0.0f,10.0f,-20.0f));
	
	_particleSystem[0] = CreateDefaultSubobject<UCascadeParticleSystemComponent>(TEXT("Treads01"));
	_particleSystem[0]->SetupAttachment(_staticMesh[1]);
	
	_staticMesh[2] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Track02"));
	_staticMesh[2]->SetupAttachment(_arrow[0]);
	_staticMesh[2]->SetRelativeLocation(FVector(0.0f,-10.0f,-20.0f));
	
	_particleSystem[1] = CreateDefaultSubobject<UCascadeParticleSystemComponent>(TEXT("Treads02"));
	_particleSystem[1]->SetupAttachment(_staticMesh[2]);
	
	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_springArm->SetupAttachment(RootComponent);
	_springArm->SetRelativeRotation(FRotator(-70.0f, 0.0f, 0.0f));
	_springArm->TargetArmLength = 500.0f ;
	_springArm->bDoCollisionTest = false;
	_springArm->bEnableCameraLag = true;
	
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_camera->SetupAttachment(_springArm);
	
	_staticMesh[3] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TCore01"));
	_staticMesh[3]->SetupAttachment(RootComponent);
	
	_staticMesh[4] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TGun01"));
	_staticMesh[4]->SetupAttachment(_staticMesh[3]);
	_staticMesh[4]->SetRelativeLocation(FVector(0.0f,15.0f,0.0f));
	
	_arrow[1] = CreateDefaultSubobject<UArrowComponent>(TEXT("W1"));
	_arrow[1]->SetupAttachment(_staticMesh[4]);
	_arrow[1]->SetRelativeLocation(FVector(34.0f,0.0f,5.5f));
	
	_arrow[2] = CreateDefaultSubobject<UArrowComponent>(TEXT("W2"));
	_arrow[2]->SetupAttachment(_staticMesh[4]);
	_arrow[2]->SetRelativeLocation(FVector(34.0f,0.0f,-5.5f));
	
	_staticMesh[5] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TGun02"));
	_staticMesh[5]->SetupAttachment(_staticMesh[3]);
	_staticMesh[5]->SetRelativeLocation(FVector(0.0f, -15.0f, 0.0f));
	
	_arrow[3] = CreateDefaultSubobject<UArrowComponent>(TEXT("W3"));
	_arrow[3]->SetupAttachment(_staticMesh[5]);
	_arrow[3]->SetRelativeLocation(FVector(34.0f, .0f, 5.5f));
	
	_arrow[4] = CreateDefaultSubobject<UArrowComponent>(TEXT("W4"));
	_arrow[4]->SetupAttachment(_staticMesh[5]);
	_arrow[4]->SetRelativeLocation(FVector(34.0f, .0f, -5.5f));
	
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
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::IMove_Implementation(float inputValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("IMOVE_IMPLEMENTATION called with value %f"), inputValue);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
		FString::Printf(TEXT("IMOVE_IMPLEMENTATION called with value %f"), inputValue));
		
}

void ATank::ITurn_Implementation(float inputValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("ITURN_IMPLEMENTATION called with value %f"), inputValue);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
		FString::Printf(TEXT("ITurn_IMPLEMENTATION called with value %f"), inputValue));
}

void ATank::IPrimaryAction_Implementation(bool inputClicked)
{
	//this one is crap  and i think it stinks cus i cant properly see it while im debugging easily
	//UE_LOG(LogTemp, Warning, TEXT("IPRIMARYACTION_IMPLEMENTATION called with value %hhd"), inputClicked);
	
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
		FString::Printf(TEXT("IPRIMARYACTION_IMPLEMENTATION called with value %hhd"), inputClicked));
}


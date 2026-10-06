// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFirstActor.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

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




// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyFirstActor.generated.h"

class UBoxComponent;

UCLASS(Abstract)
class BLASTER_API AMyFirstActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyFirstActor();
	
private:
	UPROPERTY(EditAnywhere);
	TObjectPtr<UBoxComponent> _collider;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> _staticMesh;
	
	
};

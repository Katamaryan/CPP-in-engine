// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "EndPoint.generated.h"

class USphereComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndActivatedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndReachedSignature);

UCLASS(ABSTRACT)
class BLASTER_API AEndPoint : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEndPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> _sphere;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _endMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAutoActivate;
	
	virtual void Interact_Implementation(APawn* InteractorPawn) override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void HandleCollisionStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, FHitResult SweepResult);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnEndActivatedSignature OnEndActivated;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnEndReachedSignature OnEndReached;
};

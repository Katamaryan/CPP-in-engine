// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractButton.generated.h"

class USphereComponent;

UCLASS(ABSTRACT)
class BLASTER_API AInteractButton : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _buttonMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> _sphere;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMaterialInterface> _gridGood;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMaterialInterface> _gridDanger;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<AActor>> LinkedActors;
	bool bIsPressed;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void HandleCollisionStart(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void HandleCollisionEnd(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ButtonTriggered();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ResetButton();
};

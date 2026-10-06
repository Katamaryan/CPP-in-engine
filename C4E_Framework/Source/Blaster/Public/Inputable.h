// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Inputable.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UInputable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLASTER_API IInputable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, category = "Inputable")
	void IMove(float inputValue);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, category = "Inputable")
	void ITurn(float inputValue);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, category = "Inputable")
	void IPrimaryAction(bool inputClick);
};

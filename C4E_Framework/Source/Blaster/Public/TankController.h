// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "TankController.generated.h"

class UMainUIWidget;
/**
 * 
 */
UCLASS()
class BLASTER_API ATankController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, blueprintReadWrite, category = Input)
	TObjectPtr<UInputMappingContext> MappingContext;
	
	UPROPERTY(EditAnywhere, blueprintReadWrite, category = Input)
	TObjectPtr<UInputAction> ForwardAction;
	UPROPERTY(EditAnywhere, blueprintReadWrite, category = Input)
	TObjectPtr<UInputAction> TurnAction;
	UPROPERTY(EditAnywhere, blueprintReadWrite, category = Input)
	TObjectPtr<UInputAction> FireAction;
	
	UPROPERTY(EditAnywhere, blueprintReadWrite, category = UserInterface)
	TSubclassOf<UMainUIWidget> MainUI;
	UPROPERTY(VisibleAnywhere, category = UserInterface)
	TObjectPtr<UMainUIWidget> MainUIRef;
	
private:
	void OnForward(const FInputActionInstance& Instance);
	void OnTurn(const FInputActionInstance& Instance);
	void OnFire(const FInputActionInstance& Instance);
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;
};

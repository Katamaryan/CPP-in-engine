// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"
#include "Inputable.h"
#include "Kismet/KismetSystemLibrary.h"

void ATankController::OnForward(const FInputActionInstance& Instance)
{
	if (UKismetSystemLibrary::DoesImplementInterface(GetPawn(), UInputable::StaticClass()))
	{
		IInputable::Execute_IMove(GetPawn(), Instance.GetValue().Get<float>());
	}
}

void ATankController::OnTurn(const FInputActionInstance& Instance)
{
	if (GetPawn()->Implements<UInputable>())
	{
		IInputable::Execute_ITurn(GetPawn(), Instance.GetValue().Get<float>());
	}
}

void ATankController::OnFire(const FInputActionInstance& Instance)
{
	if (GetPawn()->GetClass()->ImplementsInterface(UInputable::StaticClass()))
	{
		IInputable::Execute_IPrimaryAction(GetPawn(), Instance.GetValue().Get<bool>());
	}
}

void ATankController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (!InPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("Nothing to possess, skipping input mapping"));
		return;
	}
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (MappingContext)
		{Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}

	SetShowMouseCursor(true);
}

void ATankController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(InputComponent))
	{
		PEI->BindAction(ForwardAction, ETriggerEvent::Triggered, this, &ATankController::OnForward);
		PEI->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ATankController::OnTurn);
		PEI->BindAction(FireAction, ETriggerEvent::Triggered, this, &ATankController::OnFire);
	}
}

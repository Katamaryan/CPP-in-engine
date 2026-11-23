// Fill out your copyright notice in the Description page of Project Settings.


#include "EncounterManager.h"

#include "Interactable.h"
#include "Tank.h"
#include "TargetComponent.h"
#include "Engine/TriggerBase.h"
#include "Kismet/KismetStringLibrary.h"


// Sets default values
AEncounterManager::AEncounterManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEncounterManager::BeginPlay()
{
	Super::BeginPlay();
	
	EncounterTriggers.GetKeys(Encounters);
	
	for (int i = 0; i < Encounters.Num(); i++)
	{
		Encounters[i]->OnActorBeginOverlap.AddDynamic(this, &AEncounterManager::OnEncounterTriggered);
	}
}

void AEncounterManager::EnableTarget_Implementation(AActor* TargetActor)
{

	TargetActor->SetActorTickEnabled(true);
	TargetActor->SetActorHiddenInGame(false);	
}

void AEncounterManager::DisableTarget_Implementation(AActor* TargetActor)
{
	TargetActor->SetActorTickEnabled(false);
	TargetActor->SetActorHiddenInGame(true);
}

void AEncounterManager::ActivateEncounter_Implementation(int EncounterID)
{
	if (CompletedEncounters.Contains(EncounterID))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
		FString::Printf(TEXT("Encounter Already Completed")));
		return;
	}
	
	for (int i = 0; i < LevelEncounters.Num(); i++)
	{
		if (EncounterID == TargetEncounter.EncounterID)
		{
			TargetEncounter = LevelEncounters[i];
			break;
		}
	}
	
	if (TargetEncounter.EncounterID == -1) {return;}

	CurrentTargetCount = 0;
	for	( int i = 0; i < TargetEncounter.EncounterActors.Num(); i++)
	{
		UTargetComponent* targetComp = TargetEncounter.EncounterActors[i]->GetComponentByClass<UTargetComponent>();
		if (!IsValid(targetComp)) 
			continue;
		targetComp->OnTargetDestroyed.AddDynamic(this, &AEncounterManager::OnTargetDestroyed);
		CurrentTargetCount++;
		targetComp->ActivateTarget();
	}
	
	FString ActiveEncounterString = "";
	ActiveEncounterString = "Encounter " + UKismetStringLibrary::Conv_IntToString(TargetEncounter.EncounterID) + " Started: ";
	ActiveEncounterString = ActiveEncounterString + UKismetStringLibrary::Conv_IntToString(CurrentTargetCount) + "targets";
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
		ActiveEncounterString);
	
	OnEncounterStarted.Broadcast(CurrentTargetCount);
	
	for (int i = 0; i < TargetEncounter.StartInteractors.Num(); i++)
	{
		if (TargetEncounter.StartInteractors[i]->Implements<UInteractable>())
		{
			IInteractable::Execute_Interact(TargetEncounter.StartInteractors[i], nullptr);
		}
	}
}

void AEncounterManager::EncounterCompleted_Implementation()
{
	CurrentTargetCount = 0;
	CompletedEncounters.Add(TargetEncounter.EncounterID);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
		FString::Printf(TEXT("Encounter Completed")));
	OnEncounterEnded.Broadcast();
	
	for (int i= 0; i < TargetEncounter.EndInteractors.Num(); i++)
	{
		if (TargetEncounter.EndInteractors[i]->Implements<UInteractable>())
		{
			IInteractable::Execute_Interact(TargetEncounter.EndInteractors[i], nullptr);
		}
	}
	
	TargetEncounter.EncounterID = -1;
	
	if (LevelEncounters.Num() == CompletedEncounters.Num())
	{
		OnEncountersCompleted.Broadcast();
	}
}

void AEncounterManager::OnTargetDestroyed_Implementation()
{
	CurrentTargetCount--;
	if (CurrentTargetCount <= 0)
	{
		EncounterCompleted();
	}
	OnTargetCountUpdated.Broadcast(CurrentTargetCount);
}

void AEncounterManager::OnEncounterTriggered_Implementation(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->IsA(ATank::StaticClass()))
	{
		
		ATriggerBase* trigger = Cast<ATriggerBase>(OverlappedActor);
		int* ID = EncounterTriggers.Find(trigger) ;
		if (ID)
		{
			ActivateEncounter(*ID);
		}
		trigger->SetActorEnableCollision(false);
	}
}




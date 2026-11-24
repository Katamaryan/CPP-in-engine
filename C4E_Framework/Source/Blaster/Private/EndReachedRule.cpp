// Fill out your copyright notice in the Description page of Project Settings.


#include "EndReachedRule.h"

#include "EndPoint.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UEndReachedRule::UEndReachedRule()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEndReachedRule::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEndReachedRule::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEndReachedRule::InitRule(int ID)
{
	Super::InitRule(ID);
	
	EndPoint = Cast<AEndPoint>(UGameplayStatics::GetActorOfClass(this, AEndPoint::StaticClass()));
	
	EndPoint->OnEndReached.AddDynamic(this, &UEndReachedRule::OnEndReached);
}

void UEndReachedRule::OnEndReached_Implementation()
{
	Completed = true;
	CompleteRule();
}


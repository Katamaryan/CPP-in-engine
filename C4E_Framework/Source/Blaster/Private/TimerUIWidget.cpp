// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerUIWidget.h"

#include "FrameNumberDisplayFormat.h"
#include "TimerGameRule.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetTextLibrary.h"

void UTimerUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	TimerRule = Cast<UTimerGameRule>(UGameplayStatics::GetGameMode(this)->GetComponentByClass(UTimerGameRule::StaticClass()));
	if (!IsValid(TimerRule))
	{
		T_Timer->RemoveFromParent();
		return;
	}
	TimerRule->OnTimerStarted.AddDynamic(this, &UTimerUIWidget::OnTimerStarted);
	TimerRule->OnTimerTicked.AddDynamic(this, &UTimerUIWidget::OnTimerTicked);
	TimerRule->OnTimerCompleted.AddDynamic(this, &UTimerUIWidget::OnTimerEnded);
	T_Timer->SetVisibility(ESlateVisibility::HitTestInvisible);
	OnTimerStarted();
}

void UTimerUIWidget::UpdateText_Implementation(float Seconds)
{
	T_Timer->SetText(UKismetTextLibrary::AsTimespan_Timespan(UKismetMathLibrary::FromSeconds(Seconds)));
}

void UTimerUIWidget::OnTimerEnded_Implementation()
{
	UpdateText(0.0f);
}

void UTimerUIWidget::OnTimerTicked_Implementation(float TimeRemaining)
{
	UpdateText(UKismetMathLibrary::Round(TimeRemaining));
}

void UTimerUIWidget::OnTimerStarted_Implementation()
{
	UpdateText(TimerRule->TimerLength);
}

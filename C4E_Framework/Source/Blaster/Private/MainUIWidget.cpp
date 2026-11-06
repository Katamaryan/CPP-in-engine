// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUIWidget.h"

#include "Components/ProgressBar.h"

void UMainUIWidget::UpdateHealthBar(float newHeatlthRatio)
{
	if (HealthBar)
		HealthBar->SetPercent(newHeatlthRatio);
}

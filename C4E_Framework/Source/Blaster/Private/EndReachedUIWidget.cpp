// Fill out your copyright notice in the Description page of Project Settings.


#include "EndReachedUIWidget.h"

#include "EndPoint.h"
#include "EndReachedRule.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UEndReachedUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	EndPoint = Cast<AEndPoint>(UGameplayStatics::GetActorOfClass(this, AEndPoint::StaticClass()));
	if (IsValid(EndPoint))
	{
		if (UGameplayStatics::GetGameMode(this)->GetComponentByClass(UEndReachedRule::StaticClass()))
		{
			T_Escape->SetText(FText::FromString(FString::Printf(TEXT("Find the Exit!"))));
			if (EndPoint->bAutoActivate)
			{
				T_Escape->SetVisibility(ESlateVisibility::HitTestInvisible);
				return;
			}
			else
			{
				T_Escape->SetVisibility(ESlateVisibility::Collapsed);
				EndPoint->OnEndActivated.AddDynamic(this, &UEndReachedUIWidget::OnEndActivated);
				return;
			}
		}
	}
	T_Escape->RemoveFromParent();
}

void UEndReachedUIWidget::OnEndActivated_Implementation()
{
	
}

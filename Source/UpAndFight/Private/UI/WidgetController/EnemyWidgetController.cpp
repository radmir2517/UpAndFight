// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/EnemyWidgetController.h"

#include "AbilitySystem/UpFightAttributeSet.h"
#include "AbilitySystem/UpFightSystemComponent.h"



void UEnemyWidgetController::BindCallBacksToDependencies()
{
	UUpFightSystemComponent* ASC = CastChecked<UUpFightSystemComponent>(AbilitySystemComponent);
	UUpFightAttributeSet* AS =  CastChecked<UUpFightAttributeSet>(AttributeSet);
	ASC->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		HeathChangedDelegate.Broadcast(Data.NewValue);
	});
	ASC->GetGameplayAttributeValueChangeDelegate(AS->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		MaxHeathChangedDelegate.Broadcast(Data.NewValue);
	});
}

void UEnemyWidgetController::BroadcastInitialValues()
{
	UUpFightAttributeSet* AS =  CastChecked<UUpFightAttributeSet>(AttributeSet);
	
	HeathChangedDelegate.Broadcast(AS->GetHealth());
	MaxHeathChangedDelegate.Broadcast(AS->GetMaxHealth());
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/EnemyWidgetController.h"

#include "AbilitySystem/UpFightAttributeSet.h"
#include "AbilitySystem/UpFightSystemComponent.h"



void UEnemyWidgetController::BindCallBacksToDependencies()
{
	
	UpAbilitySystemComponent = GetUpAbilitySystemComponent();
	UpAttributeSet = GetUpAttributeSet();
	// привяжемся к делегатам изменения атрибутов здоровья врага
	UpAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UpAttributeSet->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		HeathChangedDelegate.Broadcast(Data.NewValue);
	});
	UpAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UpAttributeSet->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		MaxHeathChangedDelegate.Broadcast(Data.NewValue);
	});
}

void UEnemyWidgetController::BroadcastInitialValues()
{
	UpAttributeSet = GetUpAttributeSet();
	// передадим начальные значения врага
	HeathChangedDelegate.Broadcast(UpAttributeSet->GetHealth());
	MaxHeathChangedDelegate.Broadcast(UpAttributeSet->GetMaxHealth());
}

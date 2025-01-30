// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/UpFightAttributeSet.h"
#include "AbilitySystem/UpFightSystemComponent.h"

void UOverlayWidgetController::BindCalledDepends()
{
	Super::BindCalledDepends();
	UUpFightSystemComponent* UpFightAbilitySystemComponent = Cast<UUpFightSystemComponent>(AbilitySystemComponent);
	UUpFightAttributeSet* UpFightAttributeSet = Cast<UUpFightAttributeSet>(AttributeSet);
	
	UpFightAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UpFightAttributeSet->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		HealthChangedDelegate.Broadcast(Data.NewValue);
	});
		UpFightAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UpFightAttributeSet->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		MaxHealthChangedDelegate.Broadcast(Data.NewValue);
	});
		UpFightAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UpFightAttributeSet->GetManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		ManaChangedDelegate.Broadcast(Data.NewValue);
	});
		UpFightAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UpFightAttributeSet->GetMaxManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		MaxManaChangedDelegate.Broadcast(Data.NewValue);
	});
}

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	UUpFightAttributeSet* UpFightAttributeSet = Cast<UUpFightAttributeSet>(AttributeSet);
	HealthChangedDelegate.Broadcast(UpFightAttributeSet->GetHealth());
	MaxHealthChangedDelegate.Broadcast(UpFightAttributeSet->GetMaxHealth());
	ManaChangedDelegate.Broadcast(UpFightAttributeSet->GetMana());
	MaxManaChangedDelegate.Broadcast(UpFightAttributeSet->GetMaxMana());
}

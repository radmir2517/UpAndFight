// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/UpFightAttributeSet.h"
#include "AbilitySystem/UpFightSystemComponent.h"

void UOverlayWidgetController::BindCallBacksToDependencies()
{
	Super::BindCallBacksToDependencies();
	UUpFightSystemComponent* UpFightAbilitySystemComponent = Cast<UUpFightSystemComponent>(AbilitySystemComponent);
	UUpFightAttributeSet* UpFightAttributeSet = Cast<UUpFightAttributeSet>(AttributeSet);

	checkf(MessageWidgetDataTable, TEXT("Add a MessageWidgetDataTable to the OverlayWidgetController"));
	
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

	// после применения эффекта мы будем получать теги эффекта и если оно совпадет с зельями выведем на экран
	UpFightAbilitySystemComponent->EffectAssetTagsDelegate.AddLambda([this](const FGameplayTagContainer& AssetTags)
	{
		for(const FGameplayTag& Tag : AssetTags)
		{
			FUIWidgetRow* Row = GetDataRowFromTable<FUIWidgetRow>(MessageWidgetDataTable, Tag);
			EffectMessageDelegate.Broadcast(*Row);
		}
	});
}

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	UUpFightAttributeSet* UpFightAttributeSet = Cast<UUpFightAttributeSet>(AttributeSet);
	MaxHealthChangedDelegate.Broadcast(UpFightAttributeSet->GetMaxHealth());
	HealthChangedDelegate.Broadcast(UpFightAttributeSet->GetHealth());
	MaxManaChangedDelegate.Broadcast(UpFightAttributeSet->GetMaxMana());
	ManaChangedDelegate.Broadcast(UpFightAttributeSet->GetMana());
}

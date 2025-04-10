// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/SpellWidgetController.h"

#include "AbilitySystem/UpFightSystemComponent.h"

void USpellWidgetController::BindCallBacksToDependencies()
{
	Super::BindCallBacksToDependencies();

	UpAbilitySystemComponent = GetUpAbilitySystemComponent();

	UpAbilitySystemComponent->AbilityGivenDelegate.AddLambda([this]()
	{
		OnInitializeStartupAbilities();
	});
}

void USpellWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	if (IsValid(UpAbilitySystemComponent))
	{
		OnInitializeStartupAbilities();
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/SpellWidgetController.h"

#include "UpFightGameplayTags.h"
#include "AbilitySystem/UpFightSystemComponent.h"
#include "Player/UpFightPlayerState.h"

void USpellWidgetController::BindCallBacksToDependencies()
{
	Super::BindCallBacksToDependencies();
	
	GetUpPlayerState();
	UpPlayerState->OnSpellPointsDelegate.AddLambda([this](int32 NewPoints)
	{
		SpellPointsDelegate.Broadcast(NewPoints);
	});
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
		// обновим очки SPellPoints
		SpellPointsDelegate.Broadcast(UpPlayerState->GetSpellPoints());
	}
}

void USpellWidgetController::ClickOnSpellGlobeButton(const FGameplayTag AbilityTag)
{
	GetUpAbilitySystemComponent();
	CurrentSpellGlobe.AbilitySpec = UpAbilitySystemComponent->GetAbilitySpecByAbilityTag(AbilityTag);
	if (CurrentSpellGlobe.AbilitySpec)
	{
		CurrentSpellGlobe.StatusTag = UpAbilitySystemComponent->GetStatusTagFromSpec(*CurrentSpellGlobe.AbilitySpec);

		if (CurrentSpellGlobe.StatusTag == FUpFightGameplayTags::Get().Abilities_Status_Locked)
		{
			OnSpellGlobeClickedDelegate.Broadcast(false);
		}
		else 
		{
			OnSpellGlobeClickedDelegate.Broadcast(true);
		}
	}
	else 
	{
		OnSpellGlobeClickedDelegate.Broadcast(false);
	}
}
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

	UpAbilitySystemComponent->SpellMenuUpdateDelegate.AddLambda([this]()
	{
		BroadcastInitialValues();
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

void USpellWidgetController::ClickOnSpellGlobeButton(const FGameplayTag AbilityTag, UUpFightUserWidget* WBP_SpellWidget)
{
	GetUpAbilitySystemComponent();
	CurrentSpellGlobe.AbilitySpec = UpAbilitySystemComponent->GetAbilitySpecByAbilityTag(AbilityTag);
	if (CurrentSpellGlobe.AbilitySpec)
	{
		CurrentSpellGlobe.StatusTag = UpAbilitySystemComponent->GetStatusTagFromSpec(*CurrentSpellGlobe.AbilitySpec);
		CurrentSpellGlobe.AbilityTag = AbilityTag;
		if (CurrentSpellGlobe.StatusTag == FUpFightGameplayTags::Get().Abilities_Status_Locked)
		{
			OnSpellGlobeClickedDelegate.Broadcast(false,WBP_SpellWidget);
		}
		else 
		{	// если тег не Locked и SpellPoints > 0, то кнопка активна
			if (GetUpPlayerState()->GetSpellPoints() > 0)
			{
				OnSpellGlobeClickedDelegate.Broadcast(true,WBP_SpellWidget);
			}
			else
			{ // если очки == 0 и тег не Locked
				OnSpellGlobeClickedDelegate.Broadcast(false,WBP_SpellWidget);
			}
		}
	}
	else // если что-то не так, то на всякий отправляем не активировать кнопку
	{
		OnSpellGlobeClickedDelegate.Broadcast(false,WBP_SpellWidget);
	}
}

void USpellWidgetController::ClickOnSpendButton()
{	// проверим на всякий, что все валидно
	if (CurrentSpellGlobe.AbilitySpec && CurrentSpellGlobe.StatusTag != FUpFightGameplayTags::Get().Abilities_Status_Locked )
	{
		GetUpAbilitySystemComponent()->ServerUpgradeSpellPoint(CurrentSpellGlobe.AbilityTag, CurrentSpellGlobe.StatusTag);
	}
}

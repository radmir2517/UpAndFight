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

	UpAbilitySystemComponent->SpellWidgetsUpdateDelegate.AddLambda([this]()
	{
		BroadcastInitialValues();
	});
}

void USpellWidgetController::BroadcastInitialValues()
{	
	Super::BroadcastInitialValues();

	if (IsValid(UpAbilitySystemComponent))
	{ // пройдемся по AbilityInfo, если наши заклинания есть в Give то вытащим inputTag и Status, назначим в AbilityInfo и отправим во все SpellWidget(что в Overlay, что в SpellMenu)
		OnInitializeStartupAbilities();
		// обновим очки SPellPoints
		SpellPointsDelegate.Broadcast(UpPlayerState->GetSpellPoints());
	}
}

// Функция, срабатываемая при нажатии на SpellGlobe в SPellMenu
void USpellWidgetController::ClickOnSpellGlobeButton(const FGameplayTag AbilityTag, const FGameplayTag CurrentInputTag, UUpFightUserWidget* WBP_SpellWidget )
{
	GetUpAbilitySystemComponent();
	CurrentSpellGlobe.AbilitySpec = UpAbilitySystemComponent->GetAbilitySpecByAbilityTag(AbilityTag);
	// проверяем есть заклинание в пуле give
	if (CurrentSpellGlobe.AbilitySpec)
	{
		CurrentSpellGlobe.StatusTag = UpAbilitySystemComponent->GetStatusTagFromSpec(*CurrentSpellGlobe.AbilitySpec);
		CurrentSpellGlobe.AbilityTag = AbilityTag;
		CurrentSpellGlobe.InputTag = UpAbilitySystemComponent->GetInputTagFromSpec(*CurrentSpellGlobe.AbilitySpec);
		// чистим от прошлых записе
		// получаем описание заклинания
		UpAbilitySystemComponent->GetSpellDescriptions(AbilityTag,CurrentSpellGlobe.SpellDescription,CurrentSpellGlobe.NextLevelSpellDescription);
		if (CurrentSpellGlobe.StatusTag == FUpFightGameplayTags::Get().Abilities_Status_Locked)
		{// если тег Locked, то кнопка неактивна
			OnSpellGlobeClickedDelegate.Broadcast(false,WBP_SpellWidget,CurrentSpellGlobe.SpellDescription,CurrentSpellGlobe.NextLevelSpellDescription);
			// не будем включать подсветку подсказки нажатия на нижний блок заклинаний
			SelectionActivateDelegate.Broadcast(false, FGameplayTag());
		}
		else 
		{	// если тег не Locked и SpellPoints > 0, то кнопка активна 
			if (GetUpPlayerState()->GetSpellPoints() > 0)
			{
				OnSpellGlobeClickedDelegate.Broadcast(true,WBP_SpellWidget,CurrentSpellGlobe.SpellDescription,CurrentSpellGlobe.NextLevelSpellDescription);
			}
			else
			{ // если очки == 0 и тег не Locked, то кнопка неактивна
				OnSpellGlobeClickedDelegate.Broadcast(false,WBP_SpellWidget,CurrentSpellGlobe.SpellDescription,CurrentSpellGlobe.NextLevelSpellDescription);
				// не будем включать подсветку подсказки нажатия на нижний блок заклинаний
				SelectionActivateDelegate.Broadcast(true, AbilityTag);
			}
		}
	}
	else // если что-то не так, то на всякий отправляем не активировать кнопку, отправляем пустой текст в виджеты описания
	{
		CurrentSpellGlobe.SpellDescription = FString();
		CurrentSpellGlobe.NextLevelSpellDescription = FString();
		CurrentSpellGlobe.isEquipButtonPressed = false;
		OnSpellGlobeClickedDelegate.Broadcast(false,WBP_SpellWidget,CurrentSpellGlobe.SpellDescription,CurrentSpellGlobe.NextLevelSpellDescription);
		// не будем включать подсветку подсказки нажатия на нижний блок заклинаний
		SelectionActivateDelegate.Broadcast(false, FGameplayTag());
	}
}

void USpellWidgetController::ClickOnSpendButton()
{	// проверим на всякий, что все валидно
	if (CurrentSpellGlobe.AbilitySpec && CurrentSpellGlobe.StatusTag != FUpFightGameplayTags::Get().Abilities_Status_Locked )
	{
		GetUpAbilitySystemComponent()->ServerUpgradeSpellPoint(CurrentSpellGlobe.AbilityTag, CurrentSpellGlobe.StatusTag);
	}
}

void USpellWidgetController::ClickOnEquipButton()
{
	if (CurrentSpellGlobe.AbilitySpec)
	{
		SelectionActivateDelegate.Broadcast(true, CurrentSpellGlobe.AbilityTag);
		CurrentSpellGlobe.isEquipButtonPressed = true;
	}
}

void USpellWidgetController::ClickOnEquippedSpellGlobe(const FGameplayTag& NewInputTag)
{
	if (CurrentSpellGlobe.isEquipButtonPressed && CurrentSpellGlobe.AbilitySpec)
	{	// чтобы заново нельзя было нажать
		CurrentSpellGlobe.isEquipButtonPressed = false;
		// подадим пустышку, чтобы обнулить кнопку и убрать выделение на SpellGlobe
		ClickOnSpellGlobeButton(FGameplayTag(),FGameplayTag(),nullptr);
		// поменяет старый InputTag на новый и отправим обновление виджетов
		GetUpAbilitySystemComponent()->ServerSpendEquipAbility(CurrentSpellGlobe.AbilityTag, NewInputTag);
	}
}

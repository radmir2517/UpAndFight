// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/UpFightWidgetController.h"
#include "SpellWidgetController.generated.h"


class UUpFightUserWidget;

USTRUCT()
struct FCurrentSpellGlobe
{
	GENERATED_BODY()

	bool isEquipButtonPressed = false;

	FGameplayTag StatusTag;

	FGameplayTag AbilityTag;

	FGameplayTag InputTag;

	FGameplayAbilitySpec* AbilitySpec;

	FString SpellDescription = FString();

	FString NextLevelSpellDescription = FString();
};

// делегат, который передаст новое состояния кнопки Spend после ClickOnSpellGlobeButton()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnSpellGlobeClickedSignature, bool, isNeedToActivateButton, UUpFightUserWidget*, WBP_SpellWidget, FString, SpellDescription, FString, NextLevelSpellDescription);
// делегат, который передаст значение SpellPoints
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpellPointsSignature, int32, Points);
// делегат который будет активировать подсказку-выделение для SpellGlobe
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSelectionActivateSignature, bool, isNeedToActivate, const FGameplayTag&, AbilityTag);
// делегат который будет обнулять bisClickOnSpellTwice в SPell глобусах, при выборе другого чтобы при повторном нажатии он не думал, что ты нажимаешь второй раз 
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSpellGlobeReassignedSignature);
// делегат который будет активировать или деактивировать кнопку Equip в SpellMenu
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEquipButtonActivationSignature, bool, isEquipButtonActivationb);

UCLASS()
class UPANDFIGHT_API USpellWidgetController : public UUpFightWidgetController
{
	GENERATED_BODY()

public:
	
	virtual void BindCallBacksToDependencies();
	
	virtual void BroadcastInitialValues();
	// Функция, срабатываемая при нажатии на SpellGlobe в SPellMenu
	UFUNCTION(BlueprintCallable)
	void ClickOnSpellGlobeButton(const FGameplayTag AbilityTag,const FGameplayTag CurrentInputTag, UUpFightUserWidget* WBP_SpellWidget);
	// Функция, срабатываемая при нажатии на Spend в SPellMenu
	UFUNCTION(BlueprintCallable)
	void ClickOnSpendButton();
	UFUNCTION(BlueprintCallable)
	void ClickOnEquipButton();
	UFUNCTION(BlueprintCallable)
	void ClickOnEquippedSpellGlobe(const FGameplayTag& NewInputTag);

	
	FCurrentSpellGlobe CurrentSpellGlobe;

	
	UPROPERTY(BlueprintAssignable)
	FOnSpellGlobeClickedSignature OnSpellGlobeClickedDelegate;
	// делегат для передачи SPell points в SpellPointsRow
	UPROPERTY(BlueprintAssignable)
	FSpellPointsSignature SpellPointsDelegate;
	// делегат который будет активировать подсказку-выделение для SpellGlobe
	UPROPERTY(BlueprintAssignable)
	FSelectionActivateSignature SelectionActivateDelegate;
	// делегат, который будет обнулять bisClickOnSpellTwice в SPell глобусах, при выборе другого чтобы при повторном нажатии он не думал, что ты нажимаешь второй раз 
	UPROPERTY(BlueprintAssignable)
	FSpellGlobeReassignedSignature SpellGlobeReassignedDelegate;
	UPROPERTY(BlueprintAssignable)
	FEquipButtonActivationSignature EquipButtonActivationDelegate;

private:
	// функция которая в зависимости от статуса(== Unlocked; ==Equipped) будет активировать/дезактивировать кнопку Equip
	UFUNCTION()
	void EquipButtonActivation();
};

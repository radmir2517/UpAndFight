// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/UpFightWidgetController.h"
#include "SpellWidgetController.generated.h"



USTRUCT()
struct FCurrentSpellGlobe
{
	GENERATED_BODY()

	FGameplayTag StatusTag;

	FGameplayAbilitySpec* AbilitySpec;
};
// делегат, который передаст новое состояния кнопки Spend после ClickOnSpellGlobeButton()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpellGlobeClickedSignature, bool, isNeedToActivateButton);
// делегат, который передаст значение SpellPoints
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpellPointsSignature, int32, Points);

UCLASS()
class UPANDFIGHT_API USpellWidgetController : public UUpFightWidgetController
{
	GENERATED_BODY()

public:
	
	virtual void BindCallBacksToDependencies();
	
	virtual void BroadcastInitialValues();
	// Функция, срабатываемая при нажатии на SpellGlobe в SPellMenu
	UFUNCTION(BlueprintCallable)
	void ClickOnSpellGlobeButton(const FGameplayTag AbilityTag);

	FCurrentSpellGlobe CurrentSpellGlobe;

	
	UPROPERTY(BlueprintAssignable)
	FOnSpellGlobeClickedSignature OnSpellGlobeClickedDelegate;
	// делегат для передачи SPell points в SpellPointsRow
	UPROPERTY(BlueprintAssignable)
	FSpellPointsSignature SpellPointsDelegate;
};

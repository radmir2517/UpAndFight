// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UpFightSystemComponent.generated.h"

class UUpFightSystemComponent; // временно чтобы ошибка не мазолила глаза и чтобы обьявление не опускать после класса

// делегат котоырй будет передавать Asset теги эффектов в Overlay Controller там если совпадают тег с тегом EffectMessage то вызовется он
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTagsSignature,const FGameplayTagContainer& /*AssetTags*/)

// делегат котоырй будет передавать в Overlay Controller там будет запускаться Инцилизация стартовых абилок для вывода их иконок на экран
DECLARE_MULTICAST_DELEGATE(FAbilityGivenSignature)

UCLASS()
class UPANDFIGHT_API UUpFightSystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	// функция будет вызываться в персонаже героя и врага, она привязывает делегата к выхову нашей EffectApplied
	UFUNCTION()
	void AbilityActorInfoSet();
	// переберем классы всех GameplayAbilities стартовых для игрока/врага и сделаем GiveAbility
	void AddCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>> StartedGameplayAbilities);

	void AbilityInputTagHeld(FGameplayTag& GameplayTag);
	void AbilityInputTagReleased(FGameplayTag& GameplayTag);

	FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	
	// экземпляр делегата передающий теги эффекта
	FEffectAssetTagsSignature EffectAssetTagsDelegate;
	// экземпляр делегата передающий UUpFightSystemComponent в OverlayController
	FAbilityGivenSignature AbilityGivenDelegate;

	// булевая которая будет проверяться в OverlayController для вывода иконок абилок
	bool bStartupAbilityGiven = false;
protected:
	// функция передающий через делегат EffectAssetTagsDelegate в OverlayController теги примененного эффекта для вызова EffectMessage если надо
	void EffectApplied (UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle);

	// функция из AbilityComponent которая реплицируется после применения GetActivatableAbilities
	virtual void OnRep_ActivateAbilities() override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UpFightSystemComponent.generated.h"
// делегат котоырй будет передавать Asset теги эффектов в Overlay Controller там если совпадают тег с тегом EffectMessage то вызовется он
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTagsSignature,const FGameplayTagContainer& /*AssetTags*/)

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

	// экземпляр делегата передающий теги эффекта
	FEffectAssetTagsSignature EffectAssetTagsDelegate;


protected:
	// функция передающий через делегат EffectAssetTagsDelegate в OverlayController теги примененного эффекта для вызова EffectMessage если надо
	void EffectApplied (UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle);
};

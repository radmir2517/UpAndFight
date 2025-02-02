// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UpFightSystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTagsSignature,const FGameplayTagContainer& /*AssetTags*/)

UCLASS()
class UPANDFIGHT_API UUpFightSystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	// функция будет вызываться в персонаже героя и врага, она привязывает делегата к выхову нашей EffectApplied
	UFUNCTION()
	void AbilityActorInfoSet();
	
	FEffectAssetTagsSignature EffectAssetTagsDelegate; 

protected:
	void EffectApplied (UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle);
};

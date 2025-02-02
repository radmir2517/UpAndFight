// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/UpFightSystemComponent.h"

void UUpFightSystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UUpFightSystemComponent::EffectApplied);
}

void UUpFightSystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,
	FActiveGameplayEffectHandle EffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTagsDelegate.Broadcast(TagContainer);
}

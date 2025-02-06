// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/UpFightSystemComponent.h"

void UUpFightSystemComponent::AbilityActorInfoSet()
{ // привяжемся к делегату которые при применения эффекта будет вызывать функцию EffectApplied
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UUpFightSystemComponent::EffectApplied);
}

void UUpFightSystemComponent::AddCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>> StartedGameplayAbilities)
{	// переберем классы всех GameplayAbilities и сделаем GiveAbility
	for(const auto Ability : StartedGameplayAbilities)
	{
		FGameplayAbilitySpec Spec = BuildAbilitySpecFromClass(Ability,1);
		GiveAbilityAndActivateOnce(Spec);
	}
}

void UUpFightSystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,FActiveGameplayEffectHandle EffectHandle)
{	// вытащим теги и передадим в OverlayController
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTagsDelegate.Broadcast(TagContainer);
}

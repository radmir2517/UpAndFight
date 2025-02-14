// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/UpFightSystemComponent.h"

#include "AbilitySystem/Abilities/UpFightGameplayAbility.h"

void UUpFightSystemComponent::AbilityActorInfoSet()
{ // привяжемся к делегату которые при применения эффекта будет вызывать функцию EffectApplied
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UUpFightSystemComponent::EffectApplied);
}

void UUpFightSystemComponent::AddCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>> StartedGameplayAbilities)
{	// переберем классы всех GameplayAbilities и сделаем GiveAbility
	for(const TSubclassOf<UGameplayAbility>& Ability : StartedGameplayAbilities)
	{
		FGameplayAbilitySpec Spec = BuildAbilitySpecFromClass(Ability,1);
		if(const UUpFightGameplayAbility* GameplayAbility = Cast<UUpFightGameplayAbility>(Spec.Ability))
		{
			Spec.GetDynamicSpecSourceTags().AddTag(GameplayAbility->SetupInputTag);
			GiveAbility(Spec);
		}
	}
}


void UUpFightSystemComponent::AbilityInputTagHeld(FGameplayTag& GameplayTag)
{// переберем все GetActivatableAbilities и активируем заклинания
	FScopedAbilityListLock ActiveScopeLock(*this);
	for(FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if(Spec.GetDynamicSpecSourceTags().HasTagExact(GameplayTag))
		{
			AbilitySpecInputPressed(Spec);
			if(!Spec.IsActive())
			{
				TryActivateAbility(Spec.Handle);
				GEngine->AddOnScreenDebugMessage(2,3.f,FColor::Red,FString::Printf(TEXT("AbilityInputTagHeld InputTag: %s"),*GameplayTag.ToString()));
			}
		}
	}
}

void UUpFightSystemComponent::AbilityInputTagReleased(FGameplayTag& GameplayTag)
{// переберем все GetActivatableAbilities и отметим что произошел Released
	FScopedAbilityListLock ActiveScopeLock(*this);
	for(FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if(Spec.GetDynamicSpecSourceTags().HasTagExact(GameplayTag))
		{
			AbilitySpecInputReleased(Spec);
			GEngine->AddOnScreenDebugMessage(3,3.f,FColor::Red,FString::Printf(TEXT("AbilityInputTagReleased InputTag: %s"),*GameplayTag.ToString()));
		}
	}
}

void UUpFightSystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,FActiveGameplayEffectHandle EffectHandle)
{	// вытащим теги и передадим в OverlayController
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTagsDelegate.Broadcast(TagContainer);
}

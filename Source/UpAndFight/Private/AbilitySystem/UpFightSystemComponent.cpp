// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/UpFightSystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "UpFightGameplayTags.h"
#include "AbilitySystem/UpFightAbilitySystemLibrary.h"
#include "AbilitySystem/Abilities/UpFightGameplayAbility.h"
#include "AbilitySystem/Data/AbilityDataAsset.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/PlayerInterface.h"

void UUpFightSystemComponent::AbilityActorInfoSet()
{ // привяжемся к делегату которые при применения эффекта будет вызывать функцию EffectApplied
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UUpFightSystemComponent::EffectApplied);
}

void UUpFightSystemComponent::AddCharacterStartupAbilities(TArray<TSubclassOf<UGameplayAbility>> StartedGameplayAbilities)
{	// переберем классы всех GameplayAbilities и сделаем GiveAbility
	for(const TSubclassOf<UGameplayAbility>& Ability : StartedGameplayAbilities)
	{
		FGameplayAbilitySpec Spec = BuildAbilitySpecFromClass(Ability,1);
		if(const UUpFightGameplayAbility* GameplayAbility = Cast<UUpFightGameplayAbility>(Spec.Ability))
		{	// добавим тег input и тег, что он Equipped
			Spec.GetDynamicSpecSourceTags().AddTag(GameplayAbility->SetupInputTag);
			Spec.GetDynamicSpecSourceTags().AddTag(FUpFightGameplayTags::Get().Abilities_Status_Equipped);
			GiveAbility(Spec);
		}
	}
	bStartupAbilityGiven = true;
	AbilityGivenDelegate.Broadcast();
}

void UUpFightSystemComponent::AddAndActivatePassiveAbilities(
	TArray<TSubclassOf<UGameplayAbility>> PassiveGameplayAbilities)
{
	for(const TSubclassOf<UGameplayAbility> AbilityClass : PassiveGameplayAbilities)
	{
		FGameplayAbilitySpec Spec = FGameplayAbilitySpec(AbilityClass,1);
		GiveAbility(Spec);
		FGameplayTagContainer PassiveGameplayTags;
		PassiveGameplayTags.AddTag(FUpFightGameplayTags::Get().Abilities_ListenAbility);
		TryActivateAbilitiesByTag(PassiveGameplayTags);
	}

}

void UUpFightSystemComponent::AddCharacterAbilities(TSubclassOf<UGameplayAbility> GameplayAbility)
{
	FGameplayAbilitySpec Spec = BuildAbilitySpecFromClass(GameplayAbility,1);
	// если уже такая абилка уже добавлена другим способом ,то не добавляем ее заново
	for (auto Ability : GetActivatableAbilities())
	{
		if (Ability.Ability->AbilityTags.First() == Spec.Ability->AbilityTags.First())
		{
			return;
		}
	}
	// проверяем что что кастится и делаем GiveAbility
	if(const UUpFightGameplayAbility* GameplayAbility = Cast<UUpFightGameplayAbility>(Spec.Ability))
	{	// добавим status тег, что он Eligible
		Spec.GetDynamicSpecSourceTags().AddTag(FUpFightGameplayTags::Get().Abilities_Status_Locked);
		GiveAbility(Spec);
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

void UUpFightSystemComponent::UpgradeAttributes(const FGameplayTag& AttributeTag)
{
	if (GetAvatarActor()->Implements<UPlayerInterface>())
	{
		ServerUpgradeAttributes(AttributeTag);
	}
}

void UUpFightSystemComponent::ServerUpgradeAttributes_Implementation(const FGameplayTag& AttributeTag)
{
	// создадим Payload, загрузим туда тег атрибута и значение и отправляем эвент в GA_ListenForEvent
	// не забываем добавить аттрибуты EventBasedEffect
	FGameplayEventData EventData;
	EventData.EventTag = AttributeTag;
	EventData.EventMagnitude = 1.f;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetAvatarActor(),AttributeTag,EventData);
	IPlayerInterface::Execute_AddToAttributePoints(GetAvatarActor(),-1);
}


void UUpFightSystemComponent::ServerUpgradeSpellPoint_Implementation(const FGameplayTag& AbilityTag,
	const FGameplayTag& StatusTag)
{
	FGameplayAbilitySpec* AbilitySpec = GetAbilitySpecByAbilityTag(AbilityTag);
	
	if (IsValid(AbilitySpec->Ability))
	{
		AbilitySpec->Level += 1;
		IPlayerInterface::Execute_AddToSpellPoints(GetAvatarActor(),-1);
		if (StatusTag == FUpFightGameplayTags::Get().Abilities_Status_Eligible)
		{
			AbilitySpec->GetDynamicSpecSourceTags().RemoveTag(FUpFightGameplayTags::Get().Abilities_Status_Eligible);
			AbilitySpec->GetDynamicSpecSourceTags().AddTag(FUpFightGameplayTags::Get().Abilities_Status_Unlocked);
		}
		MarkAbilitySpecDirty(*AbilitySpec);
	}
}

void UUpFightSystemComponent::UpdateStatusAbilities(const int32 Level)
{
	UAbilityDataAsset* AbilityDataAsset = UUpFightAbilitySystemLibrary::GetAbilityInfo(GetAvatarActor());

	for (auto Info : AbilityDataAsset->AbilitiesInfo)
	{
		// если тега нет, то стартуем слудующий цикл
		if (!Info.AbilityTag.IsValid()) continue;
		// Если требования уровня больше чем у нас то следующий цикл
		if (Level < Info.LevelRequirement) continue;
		// если этого заклинания еще нет в Give то следующий цикл
		FGameplayAbilitySpec* AbilitySpec = GetAbilitySpecByAbilityTag(Info.AbilityTag);
		if (AbilitySpec == nullptr ) continue;

		if (AbilitySpec->GetDynamicSpecSourceTags().HasTagExact(FUpFightGameplayTags::Get().Abilities_Status_Locked))
		{
			AbilitySpec->GetDynamicSpecSourceTags().RemoveTag(FUpFightGameplayTags::Get().Abilities_Status_Locked);
			AbilitySpec->GetDynamicSpecSourceTags().AddTag(FUpFightGameplayTags::Get().Abilities_Status_Eligible);
		}
		MarkAbilitySpecDirty(*AbilitySpec);
	}
	
}

FGameplayTag UUpFightSystemComponent::GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{	// получем тег из спецификации
	if(AbilitySpec.Ability)
	{
		for(FGameplayTag Tag : AbilitySpec.Ability.Get()->AbilityTags)
		{
			if(Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities"))))
			{
				return Tag;
			}
		}
	}
	return FGameplayTag();
}

FGameplayTag UUpFightSystemComponent::GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{	// получем тег из спецификации 
	if(AbilitySpec.Ability)
	{
		for(FGameplayTag Tag : AbilitySpec.Ability.Get()->AbilityTags)
		{
			if(Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Input"))))
			{
				return Tag;
			}
		}
	}
	return FGameplayTag();
}

FGameplayTag UUpFightSystemComponent::GetStatusTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	if (IsValid(AbilitySpec.Ability))
	{
		for (FGameplayTag Tag : AbilitySpec.GetDynamicSpecSourceTags())
		{
			if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities.Status"))))
			{
				return Tag;
			}
		}
	}
	return FGameplayTag();
}

FGameplayAbilitySpec* UUpFightSystemComponent::GetAbilitySpecByAbilityTag(const FGameplayTag AbilityTag)
{
	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.Ability->AbilityTags.First().MatchesTagExact(AbilityTag))
		{
			return &Spec;
		}
	}
	return nullptr;
}

void UUpFightSystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,FActiveGameplayEffectHandle EffectHandle)
{	// вытащим теги и передадим в OverlayController
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTagsDelegate.Broadcast(TagContainer);
}

void UUpFightSystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();

	if (!bStartupAbilityGiven)
	{
		bStartupAbilityGiven = true;
		AbilityGivenDelegate.Broadcast();
	}

}

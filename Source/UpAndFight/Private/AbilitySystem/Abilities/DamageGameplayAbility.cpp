// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/DamageGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"

FDamageEffectParams UDamageGameplayAbility::MakeDefaultDamageEffectParams(AActor* TargetActor)
{
	FDamageEffectParams Params;

	Params.WoldContextObject = GetAvatarActorFromActorInfo();
	Params.GameplayEffectClass = DamageEffect;

	Params.SourceAbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	if (TargetActor)
	{
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	}

	Params.AbilityLevel = GetAbilityLevel();
	for (auto Pair : DamageTypes)
	{
		Params.DamageTagAndValue.Add(Pair.Key,Pair.Value.GetValueAtLevel(Params.AbilityLevel));
	}

	Params.DebuffChance = DebuffChance;
	Params.DebuffDamage = DebuffDamage;
	Params.DebuffDuration = DebuffDuration;
	Params.DebuffFrequency = DebuffFrequency;

	return Params;
}

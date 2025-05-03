// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/DamageGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"

FDamageEffectParams UDamageGameplayAbility::MakeDefaultDamageEffectParams(AActor* TargetActor)
{
	FDamageEffectParams Params;
	// назначаем sourceActor как WoldContextObject и класс эффекта
	Params.WoldContextObject = GetAvatarActorFromActorInfo();
	Params.GameplayEffectClass = DamageEffect;

	Params.SourceAbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	if (TargetActor)
	{
		Params.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	}
	// получаем уровень
	Params.AbilityLevel = GetAbilityLevel();
	for (auto Pair : DamageTypes)
	{
		Params.DamageTagAndValue.Add(Pair.Key,Pair.Value.GetValueAtLevel(Params.AbilityLevel));
	}
	// назначаем параметры дебаффа
	Params.DebuffChance = DebuffChance;
	Params.DebuffDamage = DebuffDamage;
	Params.DebuffDuration = DebuffDuration;
	Params.DebuffFrequency = DebuffFrequency;

	return Params;
}

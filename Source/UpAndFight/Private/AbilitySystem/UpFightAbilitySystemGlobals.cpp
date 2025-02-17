// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/UpFightAbilitySystemGlobals.h"

#include "AbilitySystem/UpFightAbilityTypes.h"

FGameplayEffectContext* UUpFightAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FUpFightGameplayEffectContext();
}

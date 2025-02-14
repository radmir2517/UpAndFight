// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/UpFightGameplayAbility.h"
#include "DamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class UPANDFIGHT_API UDamageGameplayAbility : public UUpFightGameplayAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category="Damage Properties")
	FGameplayTag DamageTag;

	UPROPERTY(EditDefaultsOnly, Category="Damage Properties")
	FScalableFloat DamageValue;
	
};

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
	// Map в котором будет тег урона и его значение
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Damage Properties")
	TMap<FGameplayTag,FScalableFloat> DamageTypes;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage Properties")
	TSubclassOf<UGameplayEffect> DamageEffect;
};

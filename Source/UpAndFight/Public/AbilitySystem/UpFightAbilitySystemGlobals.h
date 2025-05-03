// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "UpFightAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class UPANDFIGHT_API UUpFightAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
public:
	// функция, которая активируется после MakeEffectContext при создании эффекта
	 virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;

	
};

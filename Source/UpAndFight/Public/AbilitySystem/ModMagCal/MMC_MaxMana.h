// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxMana.generated.h"

/**
 * 
 */
UCLASS()
class UPANDFIGHT_API UMMC_MaxMana : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:

	// в конструктуре пропишем атрибут для захвата
	UMMC_MaxMana();
	// функция которая будет вычислятть макс мана по значению уровня и Intelligence
	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const;
	
	// для захвата атрибута нужна структура, где укажем атрибут и что нужен target в UMMC_MaxMana
	FGameplayEffectAttributeCaptureDefinition IntelligenceDef;
};

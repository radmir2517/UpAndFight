// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHealth.generated.h"

/**
 * 
 */
UCLASS()
class UPANDFIGHT_API UMMC_MaxHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	// в конструктуре пропишем атрибут для захвата
	UMMC_MaxHealth();
	// функция которая будет вычислятть макс здоровье по значению уровня и Vigor
	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const;
	
	// для захвата атрибута нужна структура, где укажем атрибут и что нужен target в UMMC_MaxHealth
	FGameplayEffectAttributeCaptureDefinition VigorDef;
};

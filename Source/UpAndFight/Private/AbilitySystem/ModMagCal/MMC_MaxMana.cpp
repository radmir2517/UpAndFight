// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCal/MMC_MaxMana.h"

#include "AbilitySystem/UpFightAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	// для захвата атрибута нужна структура, где укажем атрибут и что нужна цель
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.AttributeToCapture = UUpFightAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.bSnapshot = false;
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	if(ICombatInterface* CombatInterface = Cast<ICombatInterface> (Spec.GetContext().GetSourceObject()))
	{	// получим уровень игрока или моба
		const float PlayerLevel = CombatInterface->GetPlayerLevel();
		// далее идет структура которая будет иметь теги target, source 
		FAggregatorEvaluateParameters Params;
		Params.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
		Params.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
		// и переменная куда будет присваиваться значение атрибута
		float IntelligenceValue = 0.f;
		GetCapturedAttributeMagnitude(IntelligenceDef,Spec,Params,IntelligenceValue);
		FMath::Max(0.f,IntelligenceValue);
		// формула расчета макс мана
		return 50.f + (IntelligenceValue * 2) + (15.f * PlayerLevel);
	}
	return 0.f;
}

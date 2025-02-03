// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCal/MMC_MaxHealth.h"

#include "AbilitySystem/UpFightAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	// для захвата атрибута нужна структура, где укажем атрибут и что нужна цель
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.AttributeToCapture = UUpFightAttributeSet::GetVigorAttribute();
	VigorDef.bSnapshot = false;
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	if(ICombatInterface* CombatInterface = Cast<ICombatInterface> (Spec.GetContext().GetSourceObject()))
	{	// получим уровень игрока или моба
		const float PlayerLevel = CombatInterface->GetPlayerLevel();
		// далее идет структура которая будет иметь теги target, source 
		FAggregatorEvaluateParameters Params;
		Params.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
		Params.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
		// и переменная куда будет присваиваться значение атрибута
		float VigorValue = 0.f;
		GetCapturedAttributeMagnitude(VigorDef,Spec,Params,VigorValue);
		FMath::Max(0.f,VigorValue);
		// формула расчета макс хп
		return 80.f + (VigorValue * 2.5) + (10.f * PlayerLevel);
	}
	return 0.f;
}

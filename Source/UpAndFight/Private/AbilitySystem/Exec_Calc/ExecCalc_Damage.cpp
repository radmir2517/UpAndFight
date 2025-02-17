// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Exec_Calc/ExecCalc_Damage.h"

#include "UpFightGameplayTags.h"
#include "AbilitySystem/UpFightAttributeSet.h"

//Структура в который мы можем определять вторичные атрибуты которые будут корректировать урон персонажа
struct UpFightDamageStatics
{	// для примера возьмем броню, ее у нас нет но как пример
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArcaneResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance)
	
	UpFightDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UUpFightAttributeSet,FireResistance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UUpFightAttributeSet,LightningResistance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UUpFightAttributeSet,ArcaneResistance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UUpFightAttributeSet,PhysicalResistance,Target,false);
		
	}
	
};
// статическая  функция которая будет вовзращать синглтон структуры выше
static UpFightDamageStatics& DamageStatics()
{	// он будет лишь один до конца работы программы
	static UpFightDamageStatics DStatics;
	return DStatics;
}


UExecCalc_Damage::UExecCalc_Damage()
{	// в массив для захвата мы должны добавить атрибут, для примера это будет броня
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArcaneResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
	
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDef;

	
	FUpFightGameplayTags& GameplayTags = FUpFightGameplayTags::Get();
	TagsToCaptureDef.Add(GameplayTags.Attribute_Resistance_Fire,DamageStatics().FireResistanceDef);
	TagsToCaptureDef.Add(GameplayTags.Attribute_Resistance_Lightning,DamageStatics().LightningResistanceDef);
	TagsToCaptureDef.Add(GameplayTags.Attribute_Resistance_Arcane,DamageStatics().ArcaneResistanceDef);
	TagsToCaptureDef.Add(GameplayTags.Attribute_Resistance_Physical,DamageStatics().PhysicalResistanceDef);
	
	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
		
	AActor* SourceActor = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetASC ? TargetASC->GetAvatarActor() : nullptr;
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	
	float Damage = 0.f;
	for(const TTuple<FGameplayTag, FGameplayTag> Pair: GameplayTags.DamageTypesToResistances)
	{
		// вытащим damage из заклинания и прибавим к нашему общему урону
		const FGameplayTag& DamageTypeTag = Pair.Key;
		const FGameplayTag& ResistanceTypeTag = Pair.Value;
		// проверим содержит ли карта наш тег, если нет, то выведем ошибку
		checkf(TagsToCaptureDef.Contains(ResistanceTypeTag), TEXT("TagsToCaptureDefs doesn't contain Tag: [%s] in ExecCal_Damage"), *ResistanceTypeTag.ToString());
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = TagsToCaptureDef[ResistanceTypeTag];
		// получим значение урона, т.к у нас он SetByCaller, то мы можем вызвать его по тегу
		float DamageTypeValue = Spec.GetSetByCallerMagnitude(DamageTypeTag);
		// если данный тип урона наносит 0 то начнем след.цикл, мини оптимизация
		if(DamageTypeValue <= 0.f) continue;
		
		// создадим численное значение сопротивления и получим его численное значение атрбута цели
		float Resistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef,EvaluateParameters,Resistance);
		Resistance = FMath::Clamp(Resistance,0.f,100.f);
		// далее возьмем урон и вычтем процент сопротивления
		DamageTypeValue *= (100.f - Resistance) / 100.f;
		
		Damage += DamageTypeValue;
	}
	if(Damage==0.f) return;

	// если мы хотим захватить и получить атрибут Брони например то вот что мы делаем
	//float TargetArmor = 0.f; 
	//ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef,EvaluateParameters,Armor);
	//TargetArmor = FMath::Max(0.f,TargetArmor);

	// расчет урона если бы была броня
	//Damage *= (100 - Armor * 0.33f) / 100.f;
	
	// Создадим экземпляр стурктуры которая будет хранить атрибут урона
	const FGameplayModifierEvaluatedData EvaluatedData = FGameplayModifierEvaluatedData(UUpFightAttributeSet::GetDamageAttribute(),EGameplayModOp::Additive,Damage);
	// в выходной массив мы отправим нашу структуру с измененнным атрибутом урона
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
	
	
}

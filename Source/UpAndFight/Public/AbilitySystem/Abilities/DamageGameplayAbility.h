// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/UpFightAbilityTypes.h"
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
	// функция, которая будет создавать структуру из UpFightAbilityTypes и назначать туда важные переменные
	UFUNCTION(BlueprintCallable, Category = "DamageGameplayAbility")
	FDamageEffectParams MakeDefaultDamageEffectParams(AActor* TargetActor = nullptr);
	
	// Map в котором будет тег урона и его значение
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Damage Properties")
	TMap<FGameplayTag,FScalableFloat> DamageTypes;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage Properties")
	TSubclassOf<UGameplayEffect> DamageEffect;

	UPROPERTY(EditDefaultsOnly, Category="Damage Properties")
	float DebuffChance = 0.f;
	UPROPERTY(EditDefaultsOnly, Category="Damage Properties")
	float DebuffDamage = 0.f;
	UPROPERTY(EditDefaultsOnly, Category="Damage Properties")
	float DebuffDuration = 0.f;
	UPROPERTY(EditDefaultsOnly, Category="Damage Properties")
	float DebuffFrequency = 0.f;
	UPROPERTY(EditDefaultsOnly, Category="Damage Properties")
	float DeathImpulseMagnitude = 0.f;

	

	

	
};

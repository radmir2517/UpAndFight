// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 *  AuraGameplayTags
 *  Синглтон(Singleton) содержащий нативные геймплейные теги
 *  нативные потому что они создаются в с++ и доступны в с++
 */

// структура которая будет содержать теги атрибутов(пока secondary)
struct FUpFightGameplayTags
{
	
	static FUpFightGameplayTags& Get() {return UpFightGameplayTags;}

	static void InitializeNativeGameplayTags();


	/* Primary Attributes */
	FGameplayTag Attribute_Primary_Intelligence;
	FGameplayTag Attribute_Primary_Vigor;
	/* Secondary Attributes */
	FGameplayTag Attribute_Secondary_HealthRegeneration;
	FGameplayTag Attribute_Secondary_ManaRegeneration;
	FGameplayTag Attribute_Secondary_MaxHealth;
	FGameplayTag Attribute_Secondary_MaxMana;
	/*end Secondary Attributes */

	/* Vital Attributes */
	FGameplayTag Attribute_Vital_Health;
	FGameplayTag Attribute_Vital_Mana;
	/*end Vital Attributes */

	/* Input Tags */
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	/* end Input Tags */
	
	/* Event Tags */
	FGameplayTag Event_MontageTag_FireBolt;
	/* end Event Tags */
	
	FGameplayTag Damage;

	FGameplayTag Effect_HitReact;


private:
	// синглтон, единственный образец структуры
	static FUpFightGameplayTags UpFightGameplayTags;
};
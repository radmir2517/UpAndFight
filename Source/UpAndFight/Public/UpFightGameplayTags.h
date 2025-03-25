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
	FGameplayTag InputTag_4;
	/* end Input Tags */
	
	/* Montage Tags */
	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;
	/* end Montage Tags */
	
	/* Event Tags */
	FGameplayTag Event_Ability_Ended;
	/* end Event Tags */
	
	/* Montage Tags */
	FGameplayTag SocketLocation_Weapon;
	FGameplayTag SocketLocation_LeftHand;
	FGameplayTag SocketLocation_RightHand;
	FGameplayTag SocketLocation_Tail;
	/* end Montage Tags */
	
	/* Attack Tags */
	FGameplayTag Abilities_Attack;
	FGameplayTag Abilities_Summon;
	FGameplayTag Abilities_FireBolt;
	/* end Attack Tags */

	/* Cooldown Tags */
	FGameplayTag Cooldown_Fire_FireBolt;
	/* end Cooldown Tags */
	
	/* Damage Type Tags */
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Arcane;
	FGameplayTag Damage_Physical;
	/* end Damage Type Tags */
	// тег для мета атрибута опыта
	FGameplayTag Attribute_Meta_IncomingXP;
	
	/* Resistance Tags */
	FGameplayTag Attribute_Resistance_Fire;
	FGameplayTag Attribute_Resistance_Lightning;
	FGameplayTag Attribute_Resistance_Arcane;
	FGameplayTag Attribute_Resistance_Physical;
	/* end Resistance Tags */
	
	/* GameplayCue Tags */
	FGameplayTag GameplayCue_MeleeAttack;
	FGameplayTag GameplayCue_SpawnEffect;
	/* end GameplayCue Tags */
	
	// Карта где будут находиться тип урона и тип соответствующего для него Резиста
	TMap<FGameplayTag,FGameplayTag> DamageTypesToResistances;

	FGameplayTag Effect_HitReact;


private:
	// синглтон, единственный образец структуры
	static FUpFightGameplayTags UpFightGameplayTags;
};
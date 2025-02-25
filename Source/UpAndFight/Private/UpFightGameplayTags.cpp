// Fill out your copyright notice in the Description page of Project Settings.


#include "UpFightGameplayTags.h"

#include "GameplayTagsManager.h"

FUpFightGameplayTags FUpFightGameplayTags::UpFightGameplayTags;

void FUpFightGameplayTags::InitializeNativeGameplayTags()
{
	UGameplayTagsManager& UpFightTagsManager = UGameplayTagsManager::Get();

	// Добаление теги атрибутов
	/* Primary Attributes */
	UpFightGameplayTags.Attribute_Primary_Intelligence = UpFightTagsManager.AddNativeGameplayTag("Attribute.Primary.Intelligence", "Intelligence Attribute Tag");
	UpFightGameplayTags.Attribute_Primary_Vigor = UpFightTagsManager.AddNativeGameplayTag("Attribute.Primary.Vigor", "Vigor Attribute Tag");
	/* end Primary Attributes */
	/* Secondary Attributes */
	UpFightGameplayTags.Attribute_Secondary_HealthRegeneration = UpFightTagsManager.AddNativeGameplayTag("Attribute.Secondary.HealthRegeneration", "HealthRegeneration Attribute Tag");
	UpFightGameplayTags.Attribute_Secondary_ManaRegeneration = UpFightTagsManager.AddNativeGameplayTag("Attribute.Secondary.ManaRegeneration", "ManaRegeneration Attribute Tag");
	UpFightGameplayTags.Attribute_Secondary_MaxHealth = UpFightTagsManager.AddNativeGameplayTag("Attribute.Secondary.MaxHealth", "MaxHealth Attribute Tag");
	UpFightGameplayTags.Attribute_Secondary_MaxMana = UpFightTagsManager.AddNativeGameplayTag("Attribute.Secondary.MaxMana", "MaxMana Attribute Tag");
	/* end Secondary Attributes */
	/* Vital Attributes */
	UpFightGameplayTags.Attribute_Vital_Health = UpFightTagsManager.AddNativeGameplayTag("Attribute.Vital.Health", "Health Attribute Tag");
	UpFightGameplayTags.Attribute_Vital_Mana = UpFightTagsManager.AddNativeGameplayTag("Attribute.Vital.Mana", "Mana Attribute Tag");
	/* end Vital Attributes */

	/* InputTag */
	UpFightGameplayTags.InputTag_LMB = UpFightTagsManager.AddNativeGameplayTag("InputTag.LMB", "LMB Input Tag");
	UpFightGameplayTags.InputTag_RMB = UpFightTagsManager.AddNativeGameplayTag("InputTag.RMB", "RMB Input Tag");
	UpFightGameplayTags.InputTag_1 = UpFightTagsManager.AddNativeGameplayTag("InputTag.1", "1 Button Input Tag");
	UpFightGameplayTags.InputTag_2 = UpFightTagsManager.AddNativeGameplayTag("InputTag.2", "2 Button Input Tag");
	UpFightGameplayTags.InputTag_3 = UpFightTagsManager.AddNativeGameplayTag("InputTag.3", "3 Button Input Tag");
	/* end InputTag */

	/*  Event Tags  */
	UpFightGameplayTags.Event_MontageTag_FireBolt = UpFightTagsManager.AddNativeGameplayTag("Event.MontageTag.FireBolt", "FireBolt Event Montage Tag");
	UpFightGameplayTags.Event_MontageTag_Attack_Melee = UpFightTagsManager.AddNativeGameplayTag("Event.MontageTag.Attack.Melee", "Melee Attack Event Montage Tag");
	UpFightGameplayTags.Event_MontageTag_Attack_Ranged = UpFightTagsManager.AddNativeGameplayTag("Event.MontageTag.Attack.Ranged", "Ranged Attack Event Montage Tag");
	/* end Event Tags */

	/* Attack Tags */
	UpFightGameplayTags.Abilities_Attack= UpFightTagsManager.AddNativeGameplayTag("Abilities.Attack", "Abilities Attack Tag");
	/* end Attack Tags */
	
	UpFightGameplayTags.Effect_HitReact = UpFightTagsManager.AddNativeGameplayTag("Effect.HitReact", "HitReact Tag");

	UpFightGameplayTags.Attribute_Resistance_Fire = UpFightTagsManager.AddNativeGameplayTag("Attribute.Resistance.Fire", "Fire Resistance Tag");
	UpFightGameplayTags.Attribute_Resistance_Lightning = UpFightTagsManager.AddNativeGameplayTag("Attribute.Resistance.Lightning", "Lightning Resistance Tag");
	UpFightGameplayTags.Attribute_Resistance_Arcane = UpFightTagsManager.AddNativeGameplayTag("Attribute.Resistance.Arcane", "Arcane Resistance Tag");
	UpFightGameplayTags.Attribute_Resistance_Physical = UpFightTagsManager.AddNativeGameplayTag("Attribute.Resistance.Physical", "Physical Resistance Tag");

	
	UpFightGameplayTags.Damage_Fire = UpFightTagsManager.AddNativeGameplayTag("Damage.Fire", "Fire Damage Tag");
	UpFightGameplayTags.Damage_Lightning = UpFightTagsManager.AddNativeGameplayTag("Damage.Lightning", "Lightning Damage Tag");
	UpFightGameplayTags.Damage_Arcane = UpFightTagsManager.AddNativeGameplayTag("Damage.Arcane", "Arcane Damage Tag");
	UpFightGameplayTags.Damage_Physical = UpFightTagsManager.AddNativeGameplayTag("Damage.Physical", "Physical Damage Tag");


	UpFightGameplayTags.DamageTypesToResistances.Add(UpFightGameplayTags.Damage_Fire,UpFightGameplayTags.Attribute_Resistance_Fire);
	UpFightGameplayTags.DamageTypesToResistances.Add(UpFightGameplayTags.Damage_Lightning,UpFightGameplayTags.Attribute_Resistance_Lightning);
	UpFightGameplayTags.DamageTypesToResistances.Add(UpFightGameplayTags.Damage_Arcane,UpFightGameplayTags.Attribute_Resistance_Arcane);
	UpFightGameplayTags.DamageTypesToResistances.Add(UpFightGameplayTags.Damage_Physical,UpFightGameplayTags.Attribute_Resistance_Physical);
}

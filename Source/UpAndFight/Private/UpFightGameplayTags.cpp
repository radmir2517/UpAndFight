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

	/* MontageTag */
	UpFightGameplayTags.Event_MontageTag_FireBolt = UpFightTagsManager.AddNativeGameplayTag("Event.MontageTag.FireBolt", "FireBolt Event Montage Tag");
	/* end MontageTag */

	UpFightGameplayTags.Effect_HitReact = UpFightTagsManager.AddNativeGameplayTag("Effect.HitReact", "HitReact Tag");

	UpFightGameplayTags.Damage = UpFightTagsManager.AddNativeGameplayTag("Damage", "Damage Tag");
}

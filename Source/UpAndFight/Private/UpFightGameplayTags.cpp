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
	UpFightGameplayTags.InputTag_4 = UpFightTagsManager.AddNativeGameplayTag("InputTag.4", "4 Button Input Tag");
	/* end InputTag */

	/*  Montage Tags  */
	UpFightGameplayTags.Montage_Attack_1 = UpFightTagsManager.AddNativeGameplayTag("Montage.Attack.1", "Montage Tag");
	UpFightGameplayTags.Montage_Attack_2 = UpFightTagsManager.AddNativeGameplayTag("Montage.Attack.2", "Montage Tag");
	UpFightGameplayTags.Montage_Attack_3 = UpFightTagsManager.AddNativeGameplayTag("Montage.Attack.3", "Montage Tag");
	UpFightGameplayTags.Montage_Attack_4 = UpFightTagsManager.AddNativeGameplayTag("Montage.Attack.4", "Montage Tag");
	/*  end Montage Tags  */
	
	/* Event Tags */
	UpFightGameplayTags.Event_Ability_Ended = UpFightTagsManager.AddNativeGameplayTag("Event.Ability.Ended", "Ability Ended Tag");
	/* end Event Tags */
	
	/*  Socket Location Tags  */
	UpFightGameplayTags.SocketLocation_Weapon = UpFightTagsManager.AddNativeGameplayTag("SocketLocation.Weapon", "Socket Location Tag");
	UpFightGameplayTags.SocketLocation_LeftHand = UpFightTagsManager.AddNativeGameplayTag("SocketLocation.LeftHand", "Socket Location Tag");
	UpFightGameplayTags.SocketLocation_RightHand = UpFightTagsManager.AddNativeGameplayTag("SocketLocation.RightHand", "RightHand Socket Location Tag");
	UpFightGameplayTags.SocketLocation_Tail = UpFightTagsManager.AddNativeGameplayTag("SocketLocation.Tail", "Tail Socket Location Tag");
	/*  Socket Location Tags  */
	
	/* Attack Tags */
	UpFightGameplayTags.Abilities_Attack = UpFightTagsManager.AddNativeGameplayTag("Abilities.Attack", "Abilities Attack Tag");
	UpFightGameplayTags.Abilities_Summon = UpFightTagsManager.AddNativeGameplayTag("Abilities.Summon", "Abilities Summon Tag");
	UpFightGameplayTags.Abilities_ListenAbility = UpFightTagsManager.AddNativeGameplayTag("Abilities.ListenAbility", "Abilities ListenAbility Tag");
	UpFightGameplayTags.Abilities_Offensive_Fire_FireBolt = UpFightTagsManager.AddNativeGameplayTag("Abilities.Offensive.Fire.FireBolt", "Abilities_Offensive_Fire_FireBolt Tag");
	UpFightGameplayTags.Abilities_Offensive_Lightning_Electrocute = UpFightTagsManager.AddNativeGameplayTag("Abilities.Offensive.Lightning.Electrocute", "Abilities_Offensive_Lightning_Electrocute Tag");
	/* end Attack Tags */

	/* Passive Tags */
	UpFightGameplayTags.Abilities_Passive_1 = UpFightTagsManager.AddNativeGameplayTag("Abilities.Passive.1", "Abilities_Passive_1 Tag");;
	/* end Passive Tags */
	/* Status Tags */
	UpFightGameplayTags.Abilities_Status_Locked = UpFightTagsManager.AddNativeGameplayTag("Abilities.Status.Locked", "Ability Status - Locked  Tag");
	UpFightGameplayTags.Abilities_Status_Eligible = UpFightTagsManager.AddNativeGameplayTag("Abilities.Status.Eligible", "Ability Status - Eligible Tag");
	UpFightGameplayTags.Abilities_Status_Unlocked = UpFightTagsManager.AddNativeGameplayTag("Abilities.Status.Unlocked", "Ability Status - Unlocked  Tag");
	UpFightGameplayTags.Abilities_Status_Equipped = UpFightTagsManager.AddNativeGameplayTag("Abilities.Status.Equipped", "Ability Status - Equipped  Tag");
	/* end Status Tags */
	
	/* end Cooldown Tags */
	UpFightGameplayTags.Cooldown_Fire_FireBolt = UpFightTagsManager.AddNativeGameplayTag("Cooldown.Fire.FireBolt", "Cooldown FireBolt Tag");
	UpFightGameplayTags.Cooldown_Lightning_Electrocute= UpFightTagsManager.AddNativeGameplayTag("Cooldown.Lightning.Electrocute", "Cooldown Lightning_Electrocute Tag");
	/* Cooldown Tags */
	
	/* Damage Type Tags */
	UpFightGameplayTags.Damage_Fire = UpFightTagsManager.AddNativeGameplayTag("Damage.Fire", "Fire Damage Tag");
	UpFightGameplayTags.Damage_Lightning = UpFightTagsManager.AddNativeGameplayTag("Damage.Lightning", "Lightning Damage Tag");
	UpFightGameplayTags.Damage_Arcane = UpFightTagsManager.AddNativeGameplayTag("Damage.Arcane", "Arcane Damage Tag");
	UpFightGameplayTags.Damage_Physical = UpFightTagsManager.AddNativeGameplayTag("Damage.Physical", "Physical Damage Tag");
	/* end Damage Type Tags */

	/* Debuff Type Tags */
	UpFightGameplayTags.Debuff_Fire = UpFightTagsManager.AddNativeGameplayTag("Debuff.Fire", "Fire Debuff Tag");
	UpFightGameplayTags.Debuff_Lightning = UpFightTagsManager.AddNativeGameplayTag("Debuff.Lightning", "Lightning Debuff Tag");
	UpFightGameplayTags.Debuff_Arcane= UpFightTagsManager.AddNativeGameplayTag("Debuff.Arcane", "Arcane Debuff Tag");
	UpFightGameplayTags.Debuff_Physical = UpFightTagsManager.AddNativeGameplayTag("Debuff.Physical", "Physical Debuff Tag");
	/* end Debuff Type Tags */
	
	/* Debuff Params */
	UpFightGameplayTags.Debuff_Damage = UpFightTagsManager.AddNativeGameplayTag("Debuff.Damage", "Damage Debuff Tag");
	UpFightGameplayTags.Debuff_Chance = UpFightTagsManager.AddNativeGameplayTag("Debuff.Chance ", "Chance Debuff Tag");
	UpFightGameplayTags.Debuff_Duration= UpFightTagsManager.AddNativeGameplayTag("Debuff.Duration", "Duration Debuff Tag");
	UpFightGameplayTags.Debuff_Frequency= UpFightTagsManager.AddNativeGameplayTag("Debuff.Frequency", "Frequency Debuff Tag");
	/* end Debuff Params  */

	UpFightGameplayTags.Attribute_Meta_IncomingXP = UpFightTagsManager.AddNativeGameplayTag("Attribute.Meta.IncomingXP", "IncomingXP Damage Tag");
	
	/* Resistance Tags */
	UpFightGameplayTags.Attribute_Resistance_Fire = UpFightTagsManager.AddNativeGameplayTag("Attribute.Resistance.Fire", "Fire Resistance Tag");
	UpFightGameplayTags.Attribute_Resistance_Lightning = UpFightTagsManager.AddNativeGameplayTag("Attribute.Resistance.Lightning", "Lightning Resistance Tag");
	UpFightGameplayTags.Attribute_Resistance_Arcane = UpFightTagsManager.AddNativeGameplayTag("Attribute.Resistance.Arcane", "Arcane Resistance Tag");
	UpFightGameplayTags.Attribute_Resistance_Physical = UpFightTagsManager.AddNativeGameplayTag("Attribute.Resistance.Physical", "Physical Resistance Tag");
	/* end Resistance Tags */
	// добавление в карту тип урона и тип сопротивления 
	UpFightGameplayTags.DamageTypesToResistances.Add(UpFightGameplayTags.Damage_Fire,UpFightGameplayTags.Attribute_Resistance_Fire);
	UpFightGameplayTags.DamageTypesToResistances.Add(UpFightGameplayTags.Damage_Lightning,UpFightGameplayTags.Attribute_Resistance_Lightning);
	UpFightGameplayTags.DamageTypesToResistances.Add(UpFightGameplayTags.Damage_Arcane,UpFightGameplayTags.Attribute_Resistance_Arcane);
	UpFightGameplayTags.DamageTypesToResistances.Add(UpFightGameplayTags.Damage_Physical,UpFightGameplayTags.Attribute_Resistance_Physical);

	// добавление в карту тип урона и тип сопротивления 
	UpFightGameplayTags.DamageTypesToDebuff.Add(UpFightGameplayTags.Damage_Fire,UpFightGameplayTags.Debuff_Fire);
	UpFightGameplayTags.DamageTypesToDebuff.Add(UpFightGameplayTags.Damage_Lightning,UpFightGameplayTags.Debuff_Lightning);
	UpFightGameplayTags.DamageTypesToDebuff.Add(UpFightGameplayTags.Damage_Arcane,UpFightGameplayTags.Debuff_Arcane);
	UpFightGameplayTags.DamageTypesToDebuff.Add(UpFightGameplayTags.Damage_Physical,UpFightGameplayTags.Debuff_Physical);
	/* GameplayCue Tags */
	UpFightGameplayTags.GameplayCue_MeleeAttack = UpFightTagsManager.AddNativeGameplayTag("GameplayCue.MeleeAttack", "GameplayCue MeleeAttack");
	UpFightGameplayTags.GameplayCue_SpawnEffect = UpFightTagsManager.AddNativeGameplayTag("GameplayCue.SpawnEffect", "GameplayCue SpawnEffect");
	/* end GameplayCue Tags */
	
	UpFightGameplayTags.Effect_HitReact = UpFightTagsManager.AddNativeGameplayTag("Effect.HitReact", "HitReact Tag");
	
}

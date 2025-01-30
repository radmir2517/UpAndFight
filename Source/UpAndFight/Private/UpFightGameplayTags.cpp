// Fill out your copyright notice in the Description page of Project Settings.


#include "UpFightGameplayTags.h"

#include "GameplayTagsManager.h"

FUpFightGameplayTags FUpFightGameplayTags::UpFightGameplayTags;

void FUpFightGameplayTags::InitializeNativeGameplayTags()
{
	UGameplayTagsManager& UpFightTagsManager = UGameplayTagsManager::Get();

	// Добаление Vigor теги атрибутов
	UpFightGameplayTags.Attribute_Vigor_Health = UpFightTagsManager.AddNativeGameplayTag("Attribute.Vigor.Health", "Health Attribute Tag");
	UpFightGameplayTags.Attribute_Vigor_MaxHealth = UpFightTagsManager.AddNativeGameplayTag("Attribute.Vigor.MaxHealth", "MaxHealth Attribute Tag");
	UpFightGameplayTags.Attribute_Vigor_Mana = UpFightTagsManager.AddNativeGameplayTag("Attribute.Vigor.Mana", "Mana Attribute Tag");
	UpFightGameplayTags.Attribute_Vigor_MaxMana = UpFightTagsManager.AddNativeGameplayTag("Attribute.Vigor.MaxMana", "MaxMana Attribute Tag");
}

UpFightGameplayTags::UpFightGameplayTags()
{
}

UpFightGameplayTags::~UpFightGameplayTags()
{
}

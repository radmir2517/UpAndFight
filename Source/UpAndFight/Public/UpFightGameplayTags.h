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

	FGameplayTag Attribute_Vigor_Health;

	FGameplayTag Attribute_Vigor_MaxHealth;

	FGameplayTag Attribute_Vigor_Mana;

	FGameplayTag Attribute_Vigor_MaxMana;


private:
	// синглтон, единственный образец структуры
	static FUpFightGameplayTags UpFightGameplayTags;
};



class UPANDFIGHT_API UpFightGameplayTags
{
public:
	UpFightGameplayTags();
	~UpFightGameplayTags();
};
